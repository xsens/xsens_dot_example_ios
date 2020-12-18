//
//  XsensDotDevice.h
//  XsensDotSdk
//
//  Created by Nick Yang on 2019/5/19.
//  Copyright © 2019 Xsens. All rights reserved.
//

#import <CoreBluetooth/CoreBluetooth.h>
#import "XsensDotBatteryInfo.h"
#import "XsensDotFirmwareVersion.h"
#import "XsensDotPlotData.h"
#import "XsensDotStatisticsInfo.h"
#import "XsensDotUpdatePacket.h"
#import "XsensDotRecording.h"
#import "XsensDotFilterProfile.h"
#import "XsensDotDefine.h"

NS_ASSUME_NONNULL_BEGIN

@protocol CBPeripherialServiceExplorieDelegate <NSObject>
- (void)peripheral:(CBPeripheral *)peripheral serviceExplorieComplete:(BOOL)flag;
@end

@interface XsensDotDevice : NSObject

@property (strong, nonatomic, readonly) CBPeripheral *peripheral;
@property (weak, nonatomic) id<CBPeripherialServiceExplorieDelegate> explorieDelegate;
@property (strong, nonatomic, readonly) NSString *uuid;
@property (strong, nonatomic, readonly) NSString *macAddress;
/// The RSSI signal after XsensDotConnectionManager scan.
@property (strong, nonatomic, nullable) NSNumber *RSSI;
@property (copy, nonatomic) void (^onReadRSSIBlock)(NSNumber *RSSI);
@property (strong, nonatomic, nullable) XsensDotBatteryInfo *battery;
@property (strong, nonatomic) XsensDotFirmwareVersion *firmwareVersion;
@property (assign, nonatomic) UInt64 serialNumber;

@property (assign, nonatomic) BOOL plotMeasureEnable;
@property (assign, nonatomic) XSBleDevicePayloadMode plotMeasureMode;
@property (assign, nonatomic) BOOL plotLogEnable;
@property (assign, nonatomic) BOOL connectionMarkFlag;
// OTA
@property (copy, nonatomic) void (^updateProgress)(float progress);
@property (copy, nonatomic) void (^updateResult)(XsensDotUpdatePacket *updatePacket);
// For Heading reset
@property (assign, nonatomic) BOOL isSupportHeadingReset;
@property (assign, nonatomic) XSHeadingStatus headingStatus;
@property (copy, nonatomic) void (^headingResetResult)(int result);
// Power saving
@property (assign, nonatomic) UInt8 timeoutXMinutes;
@property (assign, nonatomic) UInt8 timeoutXSeconds;
@property (assign, nonatomic) UInt8 timeoutYMinutes;
@property (assign, nonatomic) UInt8 timeoutYSeconds;

@property (assign, nonatomic) NSUInteger totalSpace;
@property (assign, nonatomic) NSUInteger usedSpace;

//Recording
@property (strong, nonatomic) XsensDotRecording *recording;
@property (strong, nonatomic) NSData *exportDataFormat;
@property (assign, nonatomic) BOOL exportLogEnable;

/// Output rate
/// Should be 1Hz, 4Hz, 10Hz, 12Hz, 15Hz, 20Hz, 30Hz and 60Hz 120Hz(only for recording modes).
@property (assign, nonatomic) int outputRate;
/// Filter index
@property (assign, nonatomic) int filterIndex;

/*
    Before recording start when you give a time to check sensor storage status.
    Uint is minutes.
 */
@property (copy, nonatomic) void (^getStorageStatusWithTime)(NSUInteger time);

+ (instancetype)deviceWithPeripheral:(CBPeripheral *)peripheral;
- (void)parseAdvertisementData:(NSDictionary *)advertisementData;
- (void)parseMacAddress:(NSData *)macAddressData;
- (BOOL)isEqual:(XsensDotDevice *)object;
- (CBPeripheralState)state;
- (BOOL)stateIsConnected;
- (BOOL)isInitialized;
- (BOOL)isSynced;
- (NSString *)peripheralName;
- (NSString *)displayName;
- (NSString *)displayAddress;
- (NSArray <XsensDotFilterProfile *> *) filterProfilesList;

@end

@interface XsensDotDevice (Instruction)
- (void)setDidParsePlotDataBlock:(void (^ _Nullable)(XsensDotPlotData * _Nonnull plotData))block;
- (void)setDidParseStatisticsInfoBlock:(void(^ _Nullable)(XsensDotStatisticsInfo * _Nonnull statisticsInfo))block;
- (void)setDeviceName:(NSString *)name;
- (void)startIdentifying;
- (void)powerOff;
- (void)readStatisticsInfo;
- (BOOL)statisticsFeatureEnable;
- (void)setDidPowerOffBlock:(void(^ _Nullable)(void))block;


/// Set the outputRate and filterIndex
/// @param outputRate outputRate
/// @param filterIndex filterIndex
- (void)setOutputRate:(int)outputRate filterIndex:(int)filterIndex;


/// Read the  device signal strength
/// After read the RSSI the @propertity RSSI will be updated
/// @param block Return block after read the RSSI
- (void)readRSSI:(void (^_Nullable)(NSNumber *signal))block;


/*
    MFM function
 */
- (void)startMfm;
// Stop MFM and return the mtb file path.
- (NSString *)stopMfm;
- (void)writeMfmResult:(NSData *)mfmData;
- (void)setDidMFMProgress:(void (^_Nullable)(NSString *address, int progress))block;
- (void)setDidMFMResult:(void (^_Nullable)(NSString *address, XSDotMFMResultTpye type))block;
/*
  OTA function
 */
- (void)setFirmwareUpdate:(NSString *)file;
/*
    Power saving
    xMinutes is advertisementMinutes, xSeconds is advertisementSeconds
    yMinutes is connectionMinutes, ySeconds is connectionSeconds
 */
- (void)setPowerSavingTimeout:(UInt8) xMinutes xSecond:(UInt8)xSeconds yMinutes:(UInt8)yMinutes ySeconds:(UInt8)ySeconds;

/*
    For Heading reset
 */
- (void)startHeadingReset;
- (void)startHeadingRevert;
- (void)setDidreadRotLocal:(void (^_Nullable)(float * _Nonnull rotLocal))block;

/*
    Crash Info
    clearCrashInfoData need dumpCrashInfoData after 150ms.
 */
- (void)dumpCrashInfoData;
- (void)clearCrashInfoData;

/*
    Synchronization for sdk use
 */
- (void)startSync:(NSString *)address type:(UInt8)type;
- (void)stopSync;
/*
    get Recording Status, after call this method the recording.recordingStatus will be update
 */
- (void)getRecordingStatus;

/*
    Start Recording recordingTime 0xff means recording until storage is full.
 */
- (void)startRecording:(UInt16)recordingTime;
- (void)stopRecording;

/*
    get flash info , this will be initializing totalSpace and usedSpace
 */
- (void)getFlashInfo;
- (void)setFlashInfoDoneBlock:(void (^_Nullable)(XSFlashInfoStatus status))block;

/*
    If recording.recordingStatus == XSRecordingIsRecording ,and  will be get the
    recording.recordingDate, recording.recordingTime ,recording.remainingTime
 */
- (void)getRecordingTime;

/*
    earse Recording Data
 */
- (void)eraseData;
- (void)setEraseDataDoneBlock:(void (^_Nullable)(int success))block;

/*
    This will be initialize RecordingFile.timeStamap
 */
- (void)getExportFileInfo;
- (void)setExportFileInfoDone:(void (^_Nullable)(BOOL success))block;

/*
     When call this method, Please ensure two prerequisites
     1. set device.exportDataFormat
     2. set recording.exportFileList
     recording export status in this block:
     recording.updateExportingStatus
 */
- (void)startExportFileData;
/*
    Recording export status in this block:
    recording.updateExportingStatus
 */
- (void)stopExportFileData;

/*
    The recording export file data block, after call this method: startExportFileData this will be notify.
 */
- (void)setDidParseExportFileDataBlock:(void (^ _Nullable)(XsensDotPlotData * _Nonnull plotData))block;

/**
  Button callback block
 */
- (void)setDidButtonCallbackBlock:(void (^ _Nullable)(int timestamp))block;

@end

NS_ASSUME_NONNULL_END
