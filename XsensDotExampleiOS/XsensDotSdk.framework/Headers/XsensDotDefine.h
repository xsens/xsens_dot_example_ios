//
//  XsensDotDefine.h
//  XsensDotSdk
//
//  Created by Nick Yang on 2019/5/13.
//  Copyright © 2019 Xsens. All rights reserved.
//

#ifndef XSENSDotDefine_h
#define XSENSDotDefine_h

#import <Foundation/Foundation.h>


extern NSString * const kCBAdvDataLocalName;
extern NSString * const kCBAdvDataManufacturerData;
extern NSInteger const XSDotDevicePoolCapacityMax;
extern float const XSDotDeviceConnectDuration;
extern float const XSDotDeviceScanDuration;


#pragma mark - XSDotManagerState

/*
Enum XSManagerState:
Bluetooth state.

Equivalent to CBManagerState, CBCentralManagerState and CBPeripheralManagerState.
The purpose is to solve the compatibility problem of CBCentralManager.state type in different versions of iOS.
*/

typedef NS_ENUM(NSInteger, XSDotManagerState)
{
    XSDotManagerStateUnknown      = 0,//CBManagerStateUnknown
    XSDotManagerStateResetting,       //CBManagerStateResetting
    XSDotManagerStateUnsupported,     //CBManagerStateUnsupported
    XSDotManagerStateUnauthorized,    //CBManagerStateUnauthorized
    XSDotManagerStatePoweredOff,      //CBManagerStatePoweredOff
    XSDotManagerStatePoweredOn,       //CBManagerStatePoweredOn
};

#pragma mark - XSDotDeviceCalibrationType

typedef NS_ENUM(NSInteger, XSDotDeviceCalibrationType)
{
    XSDotDeviceCalibrationType1Step   = 1,
    XSDotDeviceCalibrationType4Steps  = 4,
    XSDotDeviceCalibrationType7Steps  = 7,
    
    XSDotDeviceCalibrationTypeDefault = XSDotDeviceCalibrationType7Steps,
};

#pragma mark - XSDotDeviceMFMResultTpye

typedef NS_ENUM(NSUInteger, XSDotMFMResultTpye)
{
    XSDotMFMResultFailed = 0,
    XSDotMFMResultBad,
    XSDotMFMResultAcceptable,
    XSDotMFMResultGood,
};

/*
 PayloadMode of Measurement
 */
typedef NS_ENUM(NSInteger,XSBleDevicePayloadMode)
{
    XSBleDevicePayloadDefault = 0,
    XSBleDevicePayloadInertialHighFidelityWithMag,
    XSBleDevicePayloadExtendedQuaternion,
    XSBleDevicePayloadCompleteQuaternion,
    XSBleDevicePayloadOrientationEuler,
    XSBleDevicePayloadOrientationQuaternion,
    XSBleDevicePayloadFreeAcceleration,
    XSBleDevicePayloadExtendedEuler, //new payload
    XSBleDevicePayloadMFM = 15,
    XSBleDevicePayloadCompleteEuler,
    XSBleDevicePayloadHighFidelityNoMag,
    XSBleDevicePayloadDeltaQuantitiesWithMag,
    XSBleDevicePayloadDeltaQuantitiesNoMag,
    XSBleDevicePayloadRateQuantitiesWithMag,
    XSBleDevicePayloadRateQuantitiesNoMag,
    XSBleDevicePayloadCustomMode1, //new payload
    XSBleDevicePayloadCustomMode2, //new payload
    XSBleDevicePayloadCustomMode3 //new payload
};

typedef NS_ENUM(NSUInteger, XSRecordingData)
{
    XSRecordingDataTimestamp = 0x00,
    XSRecordingDataQuaternion,
    XSRecordingDataIq,
    XSRecordingDataIv, // 0x03
    XSRecordingDataEulerAngles,
    XSRecordingDataDq,
    XSRecordingDataDv,
    XSRecordingDataAcceleration,
    XSRecordingDataAngularVelocity,
    XSRecordingDataMagneticField,
    XSRecordingDataStatus,//0x0a
    XSRecordingDataClipCountAcc,
    XSRecordingDataClipCountGyr,
};

typedef NS_ENUM(NSUInteger, XSHeadingStatus)
{
    XSHeadingStatusXrmHeading = 1,
    XSHeadingStatusXrmDefaultAlignment = 7,
    XSHeadingStatusXrmNone
};

typedef NS_ENUM(NSUInteger, XsensDotBleMessageId)
{
    XsensDotBleMessageRecording = 1,
    XsensDotBleMessageSync
};

typedef NS_ENUM(NSUInteger, XsensDotBleMessageRecordingId)
{
    XSBleMessageRecordingEarseFlash = 0x30,
    XSBleMessageRecordingEraseFlashDone,
    XSBleMessageRecordingStoreFlashInfo,
    XSBleMessageRecordingStoreFlashInfoDone,
    XSBleMessageRecordingFlashFull,
    XSBleMessageRecordingInvalidFlashFormat,
    
    XSBleMessageRecordingStartRecording = 0x40,
    XSBleMessageRecordingStopRecording,
    XSBleMessageRecordingGetRecordingTime,
    XSBleMessageRecordingRecordingTime,
    
    XSBleMessageRecordingGetFlashInfo = 0x50,
    XSBleMessageRecordingFlashInfo,
    XSBleMessageRecordingFlashInfoDone,
    
    XSBleMessageRecordingGetExportFileInfo = 0x60,
    XSBleMessageRecordingExportFileInfo,
    XSBleMessageRecordingExportFileInfoDone,
    XSBleMessageRecordingExportNoFile,
    
    XSBleMessageRecordingGetExportFileData = 0x70,
    XSBleMessageRecordingExportFileData,
    XSBleMessageRecordingExportFileDataDone,
    XSBleMessageRecordingStopExportFileData
};

typedef NS_ENUM(NSUInteger, XsensDotBleMessageSyncId)
{
    XSBleMessageSyncStopSync = 0x50,
    XSBleMessageSyncGetSyncStatus = 0x51
};

typedef NS_ENUM(NSUInteger, XSBleDeviceReportType)
{
    XSBleDeviceReportTypeSuccessful = 0,
    XSBleDeviceReportTypePowerOff,
    XSBleDeviceReportTypeDeviceBusy,
    XSBleDeviceReportTypeIllegalCommand,
    XSBleDeviceReportTypePowerSaving,
    XSBleDeviceReportTypeButtonCallback,
    XSBleDeviceFilterProfileTotalNumber,
    XSBleDeviceFilterProfileProperty,
};

#pragma mark - Notification keywords
/*
 Notification keywords.
 If there is return data, use NSNotification.object to return.
 */

//Bluetooth state update
extern NSString * const kXsensDotNotificationManagerStateDidUpdate;

//Connect succeeded, return XsensDotDevice *.
extern NSString * const kXsensDotNotificationDeviceConnectSucceeded;

//Connect failed, return XsensDotDevice *.
extern NSString * const kXsensDotNotificationDeviceConnectFailed;

//Connection break, return XsensDotDevice *.
extern NSString * const kXsensDotNotificationDeviceDidDisconnect;

//Battery information update, return XsensDotDevice *.
extern NSString * const kXsensDotNotificationDeviceBatteryDidUpdate;

//Firmware version read, return XsensDotDevice *.
extern NSString * const kXsensDotNotificationDeviceFirmwareVersionDidRead;

//Device name read, return XsensDotDevice *.
extern NSString * const kXsensDotNotificationDeviceNameDidRead;

//Device Mac address read, return XsensDotDevice *.
extern NSString * const kXsensDotNotificationDeviceMacAddressDidRead;

//Start to connect device, return nil.
extern NSString * const kXsensDotNotificationDeviceConnectionDidStart;

//Logger path , when start logging return NSString *.
extern NSString * const kXsensDotNotificationDeviceLoggingPath;

//Recording state changed , when connect device this will be notify.
extern NSString * const kXsensDotNotificationDeviceRecordingStateUpdate;

//@"Xsens DOT"
extern NSString * const kXsensDotDeviceSpecialName;

#endif /* XSENSDotDefine_h */
