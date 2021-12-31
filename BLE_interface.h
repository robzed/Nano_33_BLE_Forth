/*
 * BLE_interface.h
 *
 *  Created on: 22 Dec 2021
 *      Author: Probin
 */

#ifndef BLE_INTERFACE_H_
#define BLE_INTERFACE_H_

#include "pforth-master/csrc/pf_all.h"

#ifdef __cplusplus
extern "C" {
#endif

// fetch a BLE events from handlers
cell_t BLE_event_fetch(cell_t device_ptr, cell_t characteristic_ptr);

// BLE Service class
cell_t BLESERVICE(cell_t uuid_cstring);
void BLESERVICE_ADDCHARACTERISTIC(cell_t service, cell_t characteristic);
cell_t BLESERVICE_CHARACTERISTICCOUNT(cell_t service);

// BLE Characteristic class
cell_t BLECHAR(cell_t uuid, cell_t properties, cell_t valueSize, cell_t fixed_size);
cell_t BLECHAR_WRITEVALUE(cell_t ble_characteristic, cell_t value, cell_t len);
cell_t BLECHAR_READVALUE(cell_t ble_characteristic, cell_t value, cell_t len);
void BLECHAR_SETEVENTHANDLER(cell_t ble_characteristic, cell_t event, cell_t handler_xt);
void BLECHAR_ADDDESCRIPTOR(cell_t ble_characteristic, cell_t descriptor);

// BLE Descriptor class
cell_t BLEDESCRIPTOR(cell_t uuid_cstring, cell_t string, cell_t length);

// Basic BLE class
cell_t BLE_BEGIN(void);
void BLE_END(void);
void BLE_POLL(cell_t timeout);
void BLE_SETEVENTHANDLER(cell_t BLE_device_event, cell_t handler_xt);
cell_t BLE_CONNECTED(void);
cell_t BLE_DISCONNECT(void);
cell_t BLE_ADDRESS(void);
cell_t BLE_RSSI(void);
cell_t BLE_SETADVERTISEDSERVICEUUID(cell_t advertisedServiceUuidCstring);
cell_t BLE_SETADVERTISEDSERVICE(cell_t BLE_service);
cell_t BLE_SETMANUFACTURERDATA(cell_t manufacturerData, cell_t manufacturerDataLength);
void BLE_SETLOCALNAME(cell_t localName);
void BLE_SETDEVICENAME(cell_t deviceName);
void BLE_SETAPPEARANCE(cell_t appearance);
void BLE_ADDSERVICE(cell_t BLE_service);
cell_t BLE_ADVERTISE(void);
void BLE_STOPADVERTISE(void);
cell_t BLE_CENTRAL(void);
void BLE_SETADVERTISINGINTERVAL(cell_t advertisingInterval);
void BLE_SETCONNECTIONINTERVAL(cell_t minimumConnectionInterval, cell_t maximumConnectionInterval);
void BLE_SETCONNECTABLE(cell_t connectable);
cell_t BLE_SCAN(cell_t withDuplicates);
cell_t BLE_SCANFORNAME(cell_t name, ucell_t name_length, cell_t withDuplicates);
cell_t BLE_SCANFORADDRESS(cell_t address, ucell_t address_length, cell_t withDuplicates);
cell_t BLE_SCANFORUUID(cell_t uuid, ucell_t uuid_length, cell_t withDuplicates);
void BLE_STOPSCAN(void);
cell_t BLE_AVAILABLE(void);



// stubs for PC build
#ifndef ARDUINO_ARDUINO_NANO33BLE
// fetch a BLE events from handlers
cell_t BLE_event_fetch(cell_t device_ptr, cell_t characteristic_ptr) { return 0; }

// BLE Service class
cell_t BLESERVICE(cell_t uuid_cstring) { return 0; }
void BLESERVICE_ADDCHARACTERISTIC(cell_t service, cell_t characteristic) { }
cell_t BLESERVICE_CHARACTERISTICCOUNT(cell_t service) { return 0; }

// BLE Characteristic class
cell_t BLECHAR(cell_t uuid, cell_t properties, cell_t valueSize, cell_t fixed_size) { return 0; }
cell_t BLECHAR_WRITEVALUE(cell_t ble_characteristic, cell_t value, cell_t len) { return 0; }
cell_t BLECHAR_READVALUE(cell_t ble_characteristic, cell_t value, cell_t len) { return 0; }
void BLECHAR_SETEVENTHANDLER(cell_t ble_characteristic, cell_t event, cell_t handler_xt) { }
void BLECHAR_ADDDESCRIPTOR(cell_t ble_characteristic, cell_t descriptor) { }

// BLE Descriptor class
cell_t BLEDESCRIPTOR(cell_t uuid_cstring, cell_t string, cell_t length) { return 0; }

// Basic BLE class
cell_t BLE_BEGIN(void)  { return 0; }
void BLE_END(void) { }
void BLE_POLL(cell_t timeout) { }
void BLE_SETEVENTHANDLER(cell_t BLE_device_event, cell_t handler_xt) { }
cell_t BLE_CONNECTED(void) { return 0; }
cell_t BLE_DISCONNECT(void) { return 0; }
cell_t BLE_ADDRESS(void) { return 0; }
cell_t BLE_RSSI(void) { return 0; }
cell_t BLE_SETADVERTISEDSERVICEUUID(cell_t advertisedServiceUuidCstring)  { return 0; }
cell_t BLE_SETADVERTISEDSERVICE(cell_t BLE_service)  { return 0; }
cell_t BLE_SETMANUFACTURERDATA(cell_t manufacturerData, cell_t manufacturerDataLength) { return 0; }
void BLE_SETLOCALNAME(cell_t localName) { }
void BLE_SETDEVICENAME(cell_t deviceName) { }
void BLE_SETAPPEARANCE(cell_t appearance) { }
void BLE_ADDSERVICE(cell_t BLE_service) { }
cell_t BLE_ADVERTISE(void) { return 0; }
void BLE_STOPADVERTISE(void) { }
cell_t BLE_CENTRAL(void) { return 0; }
void BLE_SETADVERTISINGINTERVAL(cell_t advertisingInterval) { }
void BLE_SETCONNECTIONINTERVAL(cell_t minimumConnectionInterval, cell_t maximumConnectionInterval) { }
void BLE_SETCONNECTABLE(cell_t connectable) { }
cell_t BLE_SCAN(cell_t withDuplicates) { return 0; }
cell_t BLE_SCANFORNAME(cell_t name, ucell_t name_length, cell_t withDuplicates)  { return 0; }
cell_t BLE_SCANFORADDRESS(cell_t address, ucell_t address_length, cell_t withDuplicates)  { return 0; }
cell_t BLE_SCANFORUUID(cell_t uuid, ucell_t uuid_length, cell_t withDuplicates)  { return 0; }
void BLE_STOPSCAN(void) { }
cell_t BLE_AVAILABLE(void) { return 0; }
#endif




























cell_t BLESERVICE(cell_t uuid_cstring);

cell_t BLEBYTESCHARACTERISTIC(cell_t uuid, cell_t properties, cell_t value, cell_t valueSize);
cell_t BLECSTRINGCHARACTERISTIC(cell_t uuid, cell_t properties, cell_t CstringValue);

cell_t BLEBOOLCHARACTERISTIC(cell_t uuid, cell_t properties);
cell_t BLEBOOLEANCHARACTERISTIC(cell_t uuid, cell_t properties);
cell_t BLECHARCHARACTERISTIC(cell_t uuid, cell_t properties);
cell_t BLEUNSIGNEDCHARCHARACTERISTIC(cell_t uuid, cell_t properties);
cell_t BLEBYTECHARACTERISTIC(cell_t uuid, cell_t properties);
cell_t BLESHORTCHARACTERISTIC(cell_t uuid, cell_t properties);
cell_t BLEUNSIGNEDSHORTCHARACTERISTIC(cell_t uuid, cell_t properties);
cell_t BLEWORDCHARACTERISTIC(cell_t uuid, cell_t properties);
cell_t BLEINTCHARACTERISTIC(cell_t uuid, cell_t properties);
cell_t BLEUNSIGNEDINTCHARACTERISTIC(cell_t uuid, cell_t properties);
cell_t BLELONGCHARACTERISTIC(cell_t uuid, cell_t properties);
cell_t BLEUNSIGNEDLONGCHARACTERISTIC(cell_t uuid, cell_t properties);
cell_t BLEFLOATCHARACTERISTIC(cell_t uuid, cell_t properties);
cell_t BLEDOUBLECHARACTERISTIC(cell_t uuid, cell_t properties);

cell_t BLEDESCRIPTOR(cell_t uuid_cstring, cell_t string, cell_t length);


#ifdef __cplusplus
}
#endif

#endif /* BLE_INTERFACE_H_ */
