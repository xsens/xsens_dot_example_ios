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
#import "XsensDotRecording.h"
#import "XsensDotFilterProfile.h"
#import "XsensDotDefine.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  Expore all CoreBluetooth services delegate, used in internal sdk , don't implement it.
 */
@protocol XsensDotCBPeripherialServiceExploreDelegate <NSObject>
- (void)peripheral:(CBPeripheral *)peripheral serviceExploreComplete:(BOOL)flag;
@end

/**
 *  XsensDotDevice represents an Xsens DOT sensor object, including basic information and operations,
 *  data measurement and data logging.
 */
@interface XsensDotDevice : NSObject

/**
 *  The CBPeripheral object
 */
@property (strong, nonatomic, readonly) CBPeripheral *peripheral;

/**
 *  The delegate object that will expore services
 */
@property (weak, nonatomic) id<XsensDotCBPeripherialServiceExploreDelegate> explorieDelegate;

/**
 *  uuid
 */
@property (strong, nonatomic, readonly) NSString *uuid;

/**
 *  Mac address
 */
@property (strong, nonatomic, readonly) NSString *macAddress;

/**
 *  The RSSI signal after XsensDotConnectionManager scan
 */
@property (strong, nonatomic, nullable) NSNumber *RSSI;

/**
 *  The XsensDotBatteryInfo object
 */
@property (strong, nonatomic, nullable) XsensDotBatteryInfo *battery;

/**
 *  The XsensDotFirmwareVersion object
 */
@property (strong, nonatomic) XsensDotFirmwareVersion *firmwareVersion;

/**
 *  The Serial number
 */
@property (strong, nonatomic) NSString *serialNumber;

/**
 *  The plotting(real- time streaming) enable flag
 */
@property (assign, nonatomic) BOOL plotMeasureEnable;

/**
 *  The current payload mode
 */
@property (assign, nonatomic) XSBleDevicePayloadMode plotMeasureMode;

/**
 *  The plotting(real- time streaming) log enable flag
 */
@property (assign, nonatomic) BOOL plotLogEnable;

/**
 *  The flag of  support heading reset feature
 */
@property (assign, nonatomic) BOOL isSupportHeadingReset;

/**
 *  The current heading status
 */
@property (assign, nonatomic) XSHeadingStatus headingStatus;

/**
 *  The heading  result block after do heading reset or revert
 *  @discussion The result != 0 means heading reset success otherwise heading reset fail.
 */
@property (copy, nonatomic) void (^headingResetResult)(int result);

/**
 *  The Advertisement timeout minutes
 */
@property (assign, nonatomic) UInt8 timeoutXMinutes;

/**
 *  The Advertisement timeout seconds
 */
@property (assign, nonatomic) UInt8 timeoutXSeconds;

/**
 *  The Connection timeout minutes
 */
@property (assign, nonatomic) UInt8 timeoutYMinutes;

/**
 *  The Connection timeout seconds
 */
@property (assign, nonatomic) UInt8 timeoutYSeconds;

/**
 *  The Sensor total storage space
 */
@property (assign, nonatomic) NSUInteger totalSpace;

/**
 *  The Sensor used storage space in recording mode.
 */
@property (assign, nonatomic) NSUInteger usedSpace;

/**
 *  The XsensDotRecording object
 */
@property (strong, nonatomic) XsensDotRecording *recording;

/**
 *  The recording export data format
 *  @discussion Examples :UInt8 bytes[4]    = { XSRecordingDataTimestamp, XSRecordingDataEulerAngles, XSRecordingDataAcceleration, XSRecordingDataAngularVelocity };
 *             NSData *exportData   = [NSData dataWithBytes:bytes length:sizeof(bytes)];
 */
@property (strong, nonatomic) NSData *exportDataFormat;

/**
 *  The log enable flag when start export recording data, if YES this will save log file to app's folder.
 */
@property (assign, nonatomic) BOOL exportLogEnable;

/**
 *  The property of outoutRate
 *  @discussion Should be 1Hz, 4Hz, 10Hz, 12Hz, 15Hz, 20Hz, 30Hz and 60Hz 120Hz(only for recording modes).
 */
@property (assign, nonatomic) int outputRate;

/**
 *  The property of outoutRate
 *  @discussion Currently only support 0 and 1
 */
@property (assign, nonatomic) int filterIndex;

/**
 *  Before recording start when you give a time to check sensor storage status. Unit is minute.
 */
@property (copy, nonatomic) void (^getStorageStatusWithTime)(NSUInteger time);

/**
 *  Constructor with a peripheral
 *  @param peripheral CBPeripheral object
 */
+ (instancetype)deviceWithPeripheral:(CBPeripheral *)peripheral;

/**
 *  Parse BLE advertisement data
 *  @param advertisementData Advertisement data
 */
- (void)parseAdvertisementData:(NSDictionary *)advertisementData;

/**
 *  Parse mac address
 *  @param macAddressData Mac address data
 */
- (void)parseMacAddress:(NSData *)macAddressData;

/**
 *  Judge the XsensDotDevice object if it's equal
 *  @param object The XsensDotDevice object
 */
- (BOOL)isEqual:(XsensDotDevice *)object;

/**
 *  The current bluetooth state
 */
- (CBPeripheralState)state;

/**
 *  The flag that BLE is connected
 */
- (BOOL)stateIsConnected;

/**
 *  The flag that the connection is initialized
 */
- (BOOL)isInitialized;

/**
 *  The flag that the sensor is synced
 */
- (BOOL)isSynced;

/**
 *  The peripheral name
 */
- (NSString *)peripheralName;

/**
 *  The tag name
 */
- (NSString *)displayName;

/**
 *  The mac address
 */
- (NSString *)displayAddress;

/**
 *  The support filter profile list
 */
- (NSArray <XsensDotFilterProfile *> *) filterProfilesList;

@end


/**
    Instruction method
 */
@interface XsensDotDevice (Instruction)
/**
 *  The plotting(real-time streaming) data block, after set plotMeasureEnable = YES, this will outout plotData
 *  @param block Return the XsensDotPlotData data
 */
- (void)setDidParsePlotDataBlock:(void (^ _Nullable)(XsensDotPlotData * _Nonnull plotData))block;

/**
 *  Set the sensor tag name
 *  @param name The tag name
 */
- (void)setDeviceName:(NSString *)name;

/**
 *  Start identifying
 */
- (void)startIdentifying;

/**
 *  Power off the sensor
 */
- (void)powerOff;

/**
 *  Read statistics info
 */
- (void)readStatisticsInfo;

/**
 *  The flat of support statistics feature
 */
- (BOOL)statisticsFeatureEnable;

/**
 *  The block when sensor did power off
 *  @param block The return block
 */
- (void)setDidPowerOffBlock:(void(^ _Nullable)(void))block;

/**
 *  Set the outputRate and filterIndex
 *  @param outputRate outputRate
 *  @param filterIndex filterIndex
 */
- (void)setOutputRate:(int)outputRate filterIndex:(int)filterIndex;

/**
 *  Read the  sensor signal strength
 *  @param block Return block after read the RSSI
 *  @discussion After read the RSSI the @propertity RSSI will also be updated
 */
- (void)readRSSI:(void (^_Nullable)(NSNumber *signal))block;

/**
 *  Start MFM
 */
- (void)startMfm;

/**
 *  Stop MFM
 *  @return The mtb file path
 */
- (NSString *)stopMfm;

/**
 *  Write mtb data to firmware
 *  @param mfmData The mtb data
 */
- (void)writeMfmResult:(NSData *)mfmData;

/**
 *  Set the progress block when start mfm
 *  @param block The block from mfm data parse
 */
- (void)setDidMFMProgress:(void (^_Nullable)(NSString *address, int progress))block;

/**
 *  Set the result block when  mfm has been done
 *  @param block The block from mfm process done
 */
- (void)setDidMFMResult:(void (^_Nullable)(NSString *address, XSDotMFMResultTpye type))block;

/**
 *  Start firmeare update
 *  @param file The firmeware file
 */
- (void)setFirmwareUpdate:(NSString *)file;

/**
 *  Set power saving time
 *  @param xMinutes The advertisement minutes
 *  @param xSeconds The advertisement seconds
 *  @param yMinutes The connection minutes
 *  @param ySeconds The connection seconds
 */
- (void)setPowerSavingTimeout:(UInt8) xMinutes xSecond:(UInt8)xSeconds yMinutes:(UInt8)yMinutes ySeconds:(UInt8)ySeconds;

/**
 *  Start heading reset
 *  @return If firmware support heading reset feature this will be YES, otherwise it's NO
 */
- (BOOL)startHeadingReset;

/**
 *  Start heading revert
 *  @return If firmware support heading reset feature this will be YES, otherwise it's NO
 */
- (BOOL)startHeadingRevert;

/**
 *  Read Rot local block
 *  @param block Return block
 */
- (void)setDidreadRotLocal:(void (^_Nullable)(float * _Nonnull rotLocal))block;

/**
 *  Dump crash data
 */
- (void)dumpCrashInfoData;

/**
 *  Clear crash data
 *  @discussion clearCrashInfoData is 150ms later then dumpCrashInfoData  .
 */
- (void)clearCrashInfoData;

/**
 *  Start synchronization
 *  @param address The sensor macAddress
 *  @param type The sync type
 */
- (void)startSync:(NSString *)address type:(UInt8)type;

/**
 *  Stop Synchronization
 */
- (void)stopSync;

/**
 *  Get Recording Status, after call this method the recording.recordingStatus will be update
 */
- (void)getRecordingStatus;

/**
 *  Start recording
 *  @param recordingTime The recording time that you want
 *  @discussion If no clear time, please set it to 0xFFFF, the recording will always do until storage is full
 *  @return If firmware support recording feature this will be YES, otherwise it's NO
 */
- (BOOL)startRecording:(UInt16)recordingTime;

/**
 *  Stop recording
 *  @return If firmware support recording feature this will be YES, otherwise it's NO
 */
- (BOOL)stopRecording;

/**
 *  Get sensor flash information, after called it will be initializing totalSpace and usedSpace
 *  @return If firmware support recording feature this will be YES, otherwise it's NO
 */
- (BOOL)getFlashInfo;

/**
 *  The  getFlashInfo done block
 *  @param block The XSFlashInfoStatus object
 */
- (void)setFlashInfoDoneBlock:(void (^_Nullable)(XSFlashInfoStatus status))block;

/**
 *  If recording.recordingStatus == XSRecordingIsRecording ,and  will be get the
 *          recording.recordingDate, recording.recordingTime ,recording.remainingTime
 *
 *  @return If firmware support recording feature this will be YES, otherwise it's NO
 */
- (BOOL)getRecordingTime;

/**
 *  Earse recording Data
 *  @return If firmware support recording feature this will be YES, otherwise it's NO
 */
- (BOOL)eraseData;

/**
 *  The eraseData done block
 *  @param block Return the success result
 */
- (void)setEraseDataDoneBlock:(void (^_Nullable)(int success))block;

/**
 *  Get the export file information , this will be initialize RecordingFile.timeStamap
 *  @return If firmware support recording feature this will be YES, otherwise it's NO
 */
- (BOOL)getExportFileInfo;

/**
 *  The getExportFileInfo done block
 *  @param block Return the success result
 */
- (void)setExportFileInfoDone:(void (^_Nullable)(BOOL success))block;

/**
 *  Start export recording file data, when call this method, Please ensure two prerequisites
 *          1. set device.exportDataFormat
 *          2. set recording.exportFileList
 *          recording export status in this block:
 *          recording.updateExportingStatus
 *
 *  @return If firmware support recording feature this will be YES, otherwise it's NO
 */
- (BOOL)startExportFileData;

/**
 *  Stop export recording file data, Recording export status in this block: recording.updateExportingStatus
 *  @return If firmware support recording feature this will be YES, otherwise it's NO
 */
- (BOOL)stopExportFileData;

/**
 *  The block of startExportFileData
 *  @param block Return the XsensDotPlotData object
 */
- (void)setDidParseExportFileDataBlock:(void (^ _Nullable)(XsensDotPlotData * _Nonnull plotData))block;

/**
 *  Button callback block
 *  @param block The timestamp block
 */
- (void)setDidButtonCallbackBlock:(void (^ _Nullable)(int timestamp))block;

#pragma mark - v2

/**
 * The sensor's hardware is V2
 */
- (BOOL)isProductV2;

/**
 * The sensor's hardware is V1
 */
- (BOOL)isProductV1;

#pragma mark - Power On Settings

/**
 *  Enable the DOT sensor to power on by USB plugin aditionally.
 *  @param isEnable The BOOL value
 */
- (BOOL)enableUsbPowerOn:(BOOL) isEnable;

/**
 *  check if the USB plugin power on is enabled or not.
 */
- (BOOL)isUsbPowerOnEnabled;

@end

NS_ASSUME_NONNULL_END
