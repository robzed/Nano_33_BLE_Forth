/*
 * BLE_interface.cpp
 *
 *  Created on: 22 Dec 2021
 *      Author: Rob Probin
 */


#include "BLE_interface.h"
#undef MIN
#undef MAX
#undef CODE_SIZE
#include <ArduinoBLE.h>
#undef MIN
#undef MAX
#undef CODE_SIZE
#include <map>

//
// The interface is a bit strange for Forth - and relies on C++ classes, and naming scope to make it clear.
//
// More information here https://www.arduino.cc/en/Reference/ArduinoBLE
//

// -------------------------------------------------------------
// Event to forth handling
// Since it's unclear how to call back into pForth, we make event dispatch an explicit call that calls the XTs

struct event_type {
	ucell_t device;			// can't be 0 if full
	ucell_t characteristic;	// 0 for device event, can't be 0 for characteristic
	ucell_t xt;				// Forth execution token
} ;
const int number_of_events = 50;		// this seems plenty? (before dropping old ones

// C array for circular queue
static event_type circular_buffer[number_of_events] = {0};
static int event_next_pointer = 0;		// always points at the next event to fill
static int event_oldest_pointer = 0;	// always points at the oldest event, except if there are no events, when oldest==next

static void BLE_event_push(BLEDevice* device, BLECharacteristic* characteristic, cell_t xt)
{
	// don't log an event without an event or an xt
	if(device == 0 || xt == 0)
	{
		return;
	}
	circular_buffer[event_next_pointer].device = (ucell_t)device;
	circular_buffer[event_next_pointer].characteristic = (ucell_t)characteristic;
	circular_buffer[event_next_pointer].xt = (ucell_t)xt;

	// next index is event to overwrite
	event_next_pointer++;
	// handle wrap
	if(event_next_pointer == number_of_events) { event_next_pointer = 0; }

	// we need to check if we've just overwritten the oldest (i.e. buffer is full)
	if(event_oldest_pointer == event_next_pointer)
	{
		event_oldest_pointer++;
		// handle wrap
		if(event_oldest_pointer == number_of_events) { event_next_pointer = 0; }
	}
}

cell_t BLE_event_fetch(cell_t device_ptr, cell_t characteristic_ptr)
{
	cell_t* device = (cell_t*)device_ptr;
	cell_t* characteristic = (cell_t*)characteristic_ptr;
	cell_t xt = 0;

	if(event_next_pointer == event_oldest_pointer)
	{
		// no event
		*device = 0;
		*characteristic = 0;
	}
	else
	{
		*device = circular_buffer[event_oldest_pointer].device;
		*characteristic = circular_buffer[event_oldest_pointer].characteristic;
		xt = circular_buffer[event_oldest_pointer].xt;
	}

	// next oldest index
	event_oldest_pointer++;
	// handle wrap
	if(event_oldest_pointer == number_of_events) { event_oldest_pointer = 0; }

	return xt;
}

// these are global
ucell_t connected_xt = 0;
ucell_t disconnected_xt = 0;
ucell_t discovered_xt = 0;

// At the moment there are only 0, 1, 2 device events
static void BLEDeviceEvent_BLEConnected_event_func(BLEDevice device)
{
	BLE_event_push(&device, 0, connected_xt);
}

static void BLEDeviceEvent_BLEDisconnected_event_func(BLEDevice device)
{
	BLE_event_push(&device, 0, disconnected_xt);
}

static void BLEDeviceEvent_BLEDiscovered_event_func(BLEDevice device)
{
	BLE_event_push(&device, 0, discovered_xt);
}

// For characteristic events, for each characteristic there can be up to 4 (1 for remote). So there are potentially characteristic * 5 xt's.
// MAP
//		inputs: characteristic, event
//		output: xt
//
// If we make 4 maps - one for each event, then it would only be indexed by characteristic
std::map<BLECharacteristic*, ucell_t> char_sub_events;
std::map<BLECharacteristic*, ucell_t> char_unsub_events;
std::map<BLECharacteristic*, ucell_t> char_read_events;
std::map<BLECharacteristic*, ucell_t> char_write_events;

// At the moment there are only 0, 1, 2, 3 characteristic events
static void BLECharacteristicEvent_BLESubscribed_event_func(BLEDevice device, BLECharacteristic characteristic)
{
	auto it = char_sub_events.find(&characteristic);
	if(it != char_sub_events.end())
	{
		ucell_t xt = it->second;
		BLE_event_push(&device, &characteristic, xt);
	}
}
static void BLECharacteristicEvent_BLEUnsubscribed_event_func(BLEDevice device, BLECharacteristic characteristic)
{
	ucell_t xt = char_unsub_events[&characteristic];
	BLE_event_push(&device, &characteristic, xt);
}
static void BLECharacteristicEvent_BLERead_event_func(BLEDevice device, BLECharacteristic characteristic)
{
	ucell_t xt = char_read_events[&characteristic];
	BLE_event_push(&device, &characteristic, xt);
}
// Written is also Updated (for remote)
static void BLECharacteristicEvent_BLEWritten_event_func(BLEDevice device, BLECharacteristic characteristic)
{
	ucell_t xt = char_write_events[&characteristic];
	BLE_event_push(&device, &characteristic, xt);
}


// --------------------------------------------------------------
//
// BLE Service class
//
// Used to enable the services board provides or interact with services a remote board provides.

/*

    BLEService()
    uuid()

    addCharacteristic()

    characteristicCount()
    hasCharacteristic()
    characteristic()
*/

cell_t BLESERVICE(cell_t uuid_cstring)
{
	return (cell_t)new BLEService((const char*)uuid_cstring);
}

void BLESERVICE_ADDCHARACTERISTIC(cell_t service, cell_t characteristic)
{
	BLEService* s = (BLEService*)service;
	BLECharacteristic* c = (BLECharacteristic*)characteristic;
	s->addCharacteristic(*c);
}

cell_t BLESERVICE_CHARACTERISTICCOUNT(cell_t service)
{
	BLEService* s = (BLEService*)service;
	return s->characteristicCount();
}

// --------------------------------------------------------------
//
// BLE Characteristic class
//
/*
Used to enable the characteristics board offers in a service or interact with characteristics a remote board provides.

    BLECharacteristic()
    uuid()
    properties()
    valueSize()
    value()
    valueLength()
    readValue()
    writeValue()
    setEventHandler()

    broadcast()
    written()
    subscribed()
    addDescriptor()

    descriptorCount()
    hasDescriptor()
    descriptor()
    canRead()
    read()
    canWrite()
    canSubscribe()
    subscribe()
    canUnsubscribe()
    unsubscribe()
    valueUpdated()
*/

cell_t BLECHAR(cell_t uuid, cell_t properties, cell_t valueSize, cell_t fixed_size)
{
	return (cell_t)new BLECharacteristic((const char*)uuid, properties, valueSize, fixed_size);
}

// Note writing an integer (signed/unsigned 8, 16, 32 bit is just a string read... so we leave the forth to deal with this)
cell_t BLECHAR_WRITEVALUE(cell_t ble_characteristic, cell_t value, cell_t len)
{
	BLECharacteristic* ble_char_ptr = (BLECharacteristic*)ble_characteristic;
	return ble_char_ptr->writeValue((uint8_t*)value, len);		// returns 1 on success, 0 on failure
}

// Note reading an integer (signed/unsigned 8, 16, 32 bit is just a string read...)
cell_t BLECHAR_READVALUE(cell_t ble_characteristic, cell_t value, cell_t len)
{
	BLECharacteristic* ble_char_ptr = (BLECharacteristic*)ble_characteristic;
	return ble_char_ptr->readValue((uint8_t*)value, len);		// returns number of bytes read
}

void BLECHAR_SETEVENTHANDLER(cell_t ble_characteristic, cell_t event, cell_t handler_xt)
{
	if(handler_xt and ble_characteristic)
	{
		BLECharacteristic* ble_char_ptr = (BLECharacteristic*)ble_characteristic;
		BLECharacteristicEventHandler handler = 0;
		switch(event) {
			case BLESubscribed:
				handler = &BLECharacteristicEvent_BLESubscribed_event_func;
				char_sub_events[ble_char_ptr] = handler_xt;
				break;
			case BLEUnsubscribed:
				handler = &BLECharacteristicEvent_BLEUnsubscribed_event_func;
				char_unsub_events[ble_char_ptr] = handler_xt;
				break;
			case BLERead:
				handler = &BLECharacteristicEvent_BLERead_event_func;
				char_read_events[ble_char_ptr] = handler_xt;
				break;
			case BLEWritten: // same as BLEUpdated
				handler = &BLECharacteristicEvent_BLEWritten_event_func;
				char_write_events[ble_char_ptr] = handler_xt;
				break;
		}
		if(handler)
		{
			ble_char_ptr->setEventHandler(event, *handler);
		}
	}
}

void BLECHAR_ADDDESCRIPTOR(cell_t ble_characteristic, cell_t descriptor)
{
	BLECharacteristic* ble_char_ptr = (BLECharacteristic*)ble_characteristic;
	ble_char_ptr->addDescriptor(*(BLEDescriptor*)descriptor);
}




// --------------------------------------------------------------
//
// BLE Descriptor class
//
/*	Used to describe a characteristic the board offers

    BLEDescriptor()
    uuid()
    valueSize()
    valueLength()
    value()
    readValue()
    read()
*/

cell_t BLEDESCRIPTOR(cell_t uuid_cstring, cell_t string, cell_t length)
{
	return (cell_t)new BLEDescriptor((const char*)uuid_cstring, (const uint8_t*)string, length);
}


// --------------------------------------------------------------
//
// Basic BLE class
// Used to enable the BLE module.
//
/*
    begin()
    end()
    poll()
    setEventHandler()

    connected()
    disconnect()
    address()
    rssi()
    setAdvertisedServiceUuid()
    setAdvertisedService()
    setManufacturerData()
    setLocalName()
    setDeviceName()
    setAppearance()
    addService()
    advertise()
    stopAdvertise()
    central()
    setAdvertisingInterval()
    setConnectionInterval()
    setConnectable()

    scan()
    scanForName()
    scanForAddress()
    scanForUuid()
    stopScan()
    available()
 */


cell_t BLE_BEGIN(void)
{
	return BLE.begin()?-1:0;
}

void BLE_END(void)
{
	return BLE.end();
}

void BLE_POLL(cell_t timeout)
{
	BLE.poll(timeout);
}

void BLE_SETEVENTHANDLER(cell_t BLE_device_event, cell_t handler_xt)
{
	if(handler_xt)
	{
		BLEDeviceEventHandler handler = 0;
		switch(BLE_device_event) {
			case BLEConnected:
				handler = &BLEDeviceEvent_BLEConnected_event_func;
				connected_xt = handler_xt;
				break;
			case BLEDisconnected:
				handler = &BLEDeviceEvent_BLEDisconnected_event_func;
				disconnected_xt = handler_xt;
				break;
			case BLEDiscovered:
				handler = &BLEDeviceEvent_BLEDiscovered_event_func;
				discovered_xt = handler_xt;
				break;
		}
		if(handler)
		{
			BLE.setEventHandler((BLEDeviceEvent)BLE_device_event, handler);
		}
	}

}

// -------------------------------------

cell_t BLE_CONNECTED(void)
{
	return BLE.connected()?-1:0;
}

cell_t BLE_DISCONNECT(void)
{
	return BLE.disconnect()?-1:0;
}

cell_t BLE_ADDRESS(void)
{
	// get the address
	String addr = BLE.address();

	// move it to a static copy of len+str. Not ideal, but probably good enough.
	const unsigned int address_size = (6*3)+10; // 6 sets of two digit hex digits plus colons. We reserve a bit of space as well.
	static unsigned char static_copy[address_size+1];
	unsigned int len = addr.length();

	//fix lengths that are too big
	len = len > address_size ? address_size : len;
	static_copy[0] = (unsigned char)len;

	// copy buffer - does the right thing regarding too long strings (and adds a zero terminator on, just in case)
	addr.getBytes(static_copy+1, len);

	return (cell_t)static_copy;
}

cell_t BLE_RSSI(void)
{
	return BLE.rssi();
}

cell_t BLE_SETADVERTISEDSERVICEUUID(cell_t advertisedServiceUuidCstring)
{
	return BLE.setAdvertisedServiceUuid((const char*)advertisedServiceUuidCstring)?-1:0;
}

cell_t BLE_SETADVERTISEDSERVICE(cell_t BLE_service)
{
	const BLEService& service = *(BLEService*)BLE_service;
	return BLE.setAdvertisedService(service)?-1:0;
}

cell_t BLE_SETMANUFACTURERDATA(cell_t manufacturerData, cell_t manufacturerDataLength)
{
	return BLE.setManufacturerData((uint8_t*) manufacturerData, manufacturerDataLength)?-1:0;
}

void BLE_SETLOCALNAME(cell_t localName)
{
	BLE.setLocalName((const char*)localName);
}

void BLE_SETDEVICENAME(cell_t deviceName)
{
	BLE.setDeviceName((const char*)deviceName);
}

void BLE_SETAPPEARANCE(cell_t appearance)
{
	BLE.setAppearance(appearance);
}

void BLE_ADDSERVICE(cell_t BLE_service)
{
	BLE.addService(*(BLEService*)BLE_service);
}

cell_t BLE_ADVERTISE(void)
{
	return BLE.advertise();
}

void BLE_STOPADVERTISE(void)
{
	BLE.stopAdvertise();
}

cell_t BLE_CENTRAL(void)
{
	return (cell_t)BLE.central();
}

void BLE_SETADVERTISINGINTERVAL(cell_t advertisingInterval)
{
	BLE.setAdvertisingInterval(advertisingInterval);
}

void BLE_SETCONNECTIONINTERVAL(cell_t minimumConnectionInterval, cell_t maximumConnectionInterval)
{
	BLE.setConnectionInterval(minimumConnectionInterval, maximumConnectionInterval);
}

void BLE_SETCONNECTABLE(cell_t connectable)
{
	BLE.setConnectable(connectable);
}

// ---------------------------------

cell_t BLE_SCAN(cell_t withDuplicates)
{
	return BLE.scan(withDuplicates);
}

cell_t BLE_SCANFORNAME(cell_t name, ucell_t name_length, cell_t withDuplicates)
{
	// arduino::String required
	String sname((const char*)name, name_length);
	return BLE.scanForName(sname, withDuplicates);
}


cell_t BLE_SCANFORADDRESS(cell_t address, ucell_t address_length, cell_t withDuplicates)
{
	// arduino::String required
	String saddress((const char*)address, address_length);
	return BLE.scanForAddress(saddress, withDuplicates);
}

cell_t BLE_SCANFORUUID(cell_t uuid, ucell_t uuid_length, cell_t withDuplicates)
{
	// arduino::String required
	String suuid((const char*)uuid, uuid_length);
	return BLE.scanForUuid(suuid, withDuplicates);
}

void BLE_STOPSCAN(void)
{
	BLE.stopScan();
}

cell_t BLE_AVAILABLE(void)
{
	return (cell_t) BLE.available();
}



// --------------------------------------------------------------
//
// BLE Device class
//
// Used to get information about the devices connected or discovered while scanning

/*
    poll()
    connected()
    disconnect()
    address()
    rssi()
    characteristic()

    discoverAttributes()
    discoverService()
    deviceName()
    appearance()
    serviceCount()
    hasService()
    service()
    characteristicCount()
    hasCharacteristic()

    hasLocalName()
    hasAdvertisedServiceUuid()
    advertisedServiceUuidCount()
    localName()
    advertisedServiceUuid()
    connect()
 */



