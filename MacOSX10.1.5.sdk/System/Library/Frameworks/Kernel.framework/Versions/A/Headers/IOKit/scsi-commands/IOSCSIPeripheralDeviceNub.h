/*
 * Copyright (c) 1998-2001 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _IOKIT_IO_SCSI_PERIPHERAL_DEVICE_NUB_H_
#define _IOKIT_IO_SCSI_PERIPHERAL_DEVICE_NUB_H_


// Probe score values
enum
{
	kPeripheralDeviceTypeNoMatch 	= 0,
	kDefaultProbeRanking 			= 5000,
	kFirstOrderRanking 				= 10000,
	kSecondOrderRanking 			= 15000,
	kThirdOrderRanking 				= 20000
};


#if defined(KERNEL) && defined(__cplusplus)

#include <IOKit/IOLib.h>
#include <IOKit/IOService.h>
#include <IOKit/IOSyncer.h>

#include <IOKit/scsi-commands/IOSCSIProtocolServices.h>
#include <IOKit/scsi-commands/SCSIPrimaryCommands.h>


class IOSCSIPeripheralDeviceNub : public IOSCSIProtocolServices
{
	
	OSDeclareDefaultStructors ( IOSCSIPeripheralDeviceNub )

private:
	
	static bool		sCompareIOProperty(	IOService * object,
										OSDictionary * table,
										char * propertyKeyName,
										bool * matches );
	
	static void		TaskCallback( SCSITaskIdentifier	completedTask );
	SCSIServiceResponse SendTask( SCSITask *request );

public:
	bool			InterrogateDevice( void );										

protected:
    // Reserve space for future expansion.
    struct IOSCSIPeripheralDeviceNubExpansionData { };
    IOSCSIPeripheralDeviceNubExpansionData *fIOSCSIPeripheralDeviceNubReserved;

	IOSCSIProtocolServices *		fProvider;
	SCSIPrimaryCommands *			fSCSIPrimaryCommandObject;
	UInt8							fDefaultInquiryCount;

    virtual bool		SendSCSICommand( 	SCSITaskIdentifier 		request, 
    										SCSIServiceResponse * 	serviceResponse,
    										SCSITaskStatus		* 	taskStatus );

    virtual SCSIServiceResponse	AbortSCSICommand( SCSITaskIdentifier request );

	// The IsProtocolServiceSupported will return true if the specified
	// feature is supported by the protocol layer.  If the service has a value that must be
	// returned, it will be returned in the serviceValue output parameter.
	virtual bool	IsProtocolServiceSupported( SCSIProtocolFeature feature, void * serviceValue );

	virtual bool	HandleProtocolServiceFeature( SCSIProtocolFeature feature, void * serviceValue );

	// We override this method in order to NOT do power management
	virtual void	InitializePowerManagement ( IOService * provider );

public:
    
    bool				init	( OSDictionary * propTable );
    virtual bool		start	( IOService * provider );
    virtual void 		stop	( IOService *  provider );

	virtual IOReturn	message ( UInt32 type, IOService * nub, void * arg );
										
	virtual void		joinPMtree ( IOService * driver );

    virtual bool		matchPropertyTable ( OSDictionary * table,
    										 SInt32 * score );

    // The ExecuteCommand method will take a SCSITask object and transport
    // it across the physical wires to the device
    virtual	void		ExecuteCommand ( SCSITaskIdentifier	request );
    
    // The AbortCommand method will abort the indicated SCSI Task object,
    // if it is possible and the SCSI Task has not already completed.
    virtual SCSIServiceResponse    	AbortCommand ( SCSITaskIdentifier	abortTask );

private:
	// Space reserved for future expansion.
    OSMetaClassDeclareReservedUnused( IOSCSIPeripheralDeviceNub, 1 );
    OSMetaClassDeclareReservedUnused( IOSCSIPeripheralDeviceNub, 2 );
    OSMetaClassDeclareReservedUnused( IOSCSIPeripheralDeviceNub, 3 );
    OSMetaClassDeclareReservedUnused( IOSCSIPeripheralDeviceNub, 4 );
    OSMetaClassDeclareReservedUnused( IOSCSIPeripheralDeviceNub, 5 );
    OSMetaClassDeclareReservedUnused( IOSCSIPeripheralDeviceNub, 6 );
    OSMetaClassDeclareReservedUnused( IOSCSIPeripheralDeviceNub, 7 );
    OSMetaClassDeclareReservedUnused( IOSCSIPeripheralDeviceNub, 8 );
    OSMetaClassDeclareReservedUnused( IOSCSIPeripheralDeviceNub, 9 );
    OSMetaClassDeclareReservedUnused( IOSCSIPeripheralDeviceNub, 10 );
    OSMetaClassDeclareReservedUnused( IOSCSIPeripheralDeviceNub, 11 );
    OSMetaClassDeclareReservedUnused( IOSCSIPeripheralDeviceNub, 12 );
    OSMetaClassDeclareReservedUnused( IOSCSIPeripheralDeviceNub, 13 );
    OSMetaClassDeclareReservedUnused( IOSCSIPeripheralDeviceNub, 14 );
    OSMetaClassDeclareReservedUnused( IOSCSIPeripheralDeviceNub, 15 );
    OSMetaClassDeclareReservedUnused( IOSCSIPeripheralDeviceNub, 16 );
};

class IOSCSILogicalUnitNub : public IOSCSIPeripheralDeviceNub
{
	
	OSDeclareDefaultStructors ( IOSCSILogicalUnitNub )

private:
	UInt8				fLogicalUnitNumber;

protected:
    // Reserve space for future expansion.
    struct IOSCSILogicalUnitNubExpansionData { };
    IOSCSILogicalUnitNubExpansionData *fIOSCSILogicalUnitNubReserved;

public:
    virtual bool		start	( IOService * provider );

	virtual void		SetLogicalUnitNumber( UInt8 newLUN );

    // The ExecuteCommand method will take a SCSITask object and transport
    // it across the physical wires to the device
    virtual	void		ExecuteCommand ( SCSITaskIdentifier	request );
    
    // The AbortCommand method will abort the indicated SCSI Task object,
    // if it is possible and the SCSI Task has not already completed.
    virtual SCSIServiceResponse    	AbortCommand ( SCSITaskIdentifier	abortTask );

private:
	// Space reserved for future expansion.
    OSMetaClassDeclareReservedUnused( IOSCSILogicalUnitNub, 1 );
    OSMetaClassDeclareReservedUnused( IOSCSILogicalUnitNub, 2 );
    OSMetaClassDeclareReservedUnused( IOSCSILogicalUnitNub, 3 );
    OSMetaClassDeclareReservedUnused( IOSCSILogicalUnitNub, 4 );
    OSMetaClassDeclareReservedUnused( IOSCSILogicalUnitNub, 5 );
    OSMetaClassDeclareReservedUnused( IOSCSILogicalUnitNub, 6 );
    OSMetaClassDeclareReservedUnused( IOSCSILogicalUnitNub, 7 );
    OSMetaClassDeclareReservedUnused( IOSCSILogicalUnitNub, 8 );
    OSMetaClassDeclareReservedUnused( IOSCSILogicalUnitNub, 9 );
    OSMetaClassDeclareReservedUnused( IOSCSILogicalUnitNub, 10 );
    OSMetaClassDeclareReservedUnused( IOSCSILogicalUnitNub, 11 );
    OSMetaClassDeclareReservedUnused( IOSCSILogicalUnitNub, 12 );
    OSMetaClassDeclareReservedUnused( IOSCSILogicalUnitNub, 13 );
    OSMetaClassDeclareReservedUnused( IOSCSILogicalUnitNub, 14 );
    OSMetaClassDeclareReservedUnused( IOSCSILogicalUnitNub, 15 );
    OSMetaClassDeclareReservedUnused( IOSCSILogicalUnitNub, 16 );
};

#endif	/* defined(KERNEL) && defined(__cplusplus) */

#endif	/* _IOKIT_IO_SCSI_PERIPHERAL_DEVICE_NUB_H_ */
