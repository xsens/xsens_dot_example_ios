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
 *  @brief The CBPeripheral object
 */
@property (strong, nonatomic, readonly) CBPeripheral *peripheral;

/**
 *  @brief The delegate object that will expore services
 */
@property (weak, nonatomic) id<XsensDotCBPeripherialServiceExploreDelegate> explorieDelegate;

/**
 *  @brief uuid
 */
@property (strong, nonatomic, readonly) NSString *uuid;

/**
 *  @brief Mac address
 */
@property (strong, nonatomic, readonly) NSString *macAddress;

/**
 *  @brief The RSSI signal after XsensDotConnectionManager scan
 */
@property (strong, nonatomic, nullable) NSNumber *RSSI;

/**
 *  @brief The XsensDotBatteryInfo object
 */
@property (strong, nonatomic, nullable) XsensDotBatteryInfo *battery;

/**
 *  @brief The XsensDotFirmwareVersion object
 */
@property (strong, nonatomic) XsensDotFirmwareVersion *firmwareVersion;

/**
 *  @brief The Serial number
 */
@property (assign, nonatomic) UInt64 serialNumber;

/**
 *  @brief The plotting(real- time streaming) enable flag
 */
@property (assign, nonatomic) BOOL plotMeasureEnable;

/**
 *  @brief The current payload mode
 */
@property (assign, nonatomic) XSBleDevicePayloadMode plotMeasureMode;

/**
 *  @brief The plotting(real- time streaming) log enable flag
 */
@property (assign, nonatomic) BOOL plotLogEnable;

/**
 *  @brief OTA progress block when start ota
 */
@property (copy, nonatomic) void (^updateProgress)(float progress);

/**
 *  @brief OTA result block
 */
@property (copy, nonatomic) void (^updateResult)(XsensDotUpdatePacket *updatePacket);

/**
 *  @brief The flag of  support heading reset feature
 */
@property (assign, nonatomic) BOOL isSupportHeadingReset;

/**
 *  @brief The current heading status
 */
@property (assign, nonatomic) XSHeadingStatus headingStatus;

/**
 *  @brief The heading  result block after do heading reset or revert
 */
@property (copy, nonatomic) void (^headingResetResult)(int result);

/**
 *  @brief The Advertisement timeout minutes
 */
@property (assign, nonatomic) UInt8 timeoutXMinutes;

/**
 *  @brief The Advertisement timeout seconds
 */
@property (assign, nonatomic) UInt8 timeoutXSeconds;

/**
 *  @brief The Connection timeout minutes
 */
@property (assign, nonatomic) UInt8 timeoutYMinutes;

/**
 *  @brief The Connection timeout seconds
 */
@property (assign, nonatomic) UInt8 timeoutYSeconds;

/**
 *  @brief The Sensor total storage space
 */
@property (assign, nonatomic) NSUInteger totalSpace;

/**
 *  @brief The Sensor used storage space in recording mode.
 */
@property (assign, nonatomic) NSUInteger usedSpace;

/**
 *  @brief The XsensDotRecording object
 */
@property (strong, nonatomic) XsensDotRecording *recording;

/**
 *  @brief The recording export data format
 *  @discussion Examples :UInt8 bytes[4]    = { XSRecordingDataTimestamp, XSRecordingDataEulerAngles, XSRecordingDataAcceleration, XSRecordingDataAngularVelocity };
 *             NSData *exportData   = [NSData dataWithBytes:bytes length:sizeof(bytes)];
 */
@property (strong, nonatomic) NSData *exportDataFormat;

/**
 *  @brief The log enable flag when start export recording data, if YES this will save log file to app's folder.
 */
@property (assign, nonatomic) BOOL exportLogEnable;

/**
 *  @brief The property of outoutRate
 *  @discussion Should be 1Hz, 4Hz, 10Hz, 12Hz, 15Hz, 20Hz, 30Hz and 60Hz 120Hz(only for recording modes).
 */
@property (assign, nonatomic) int outputRate;

/**
 *  @brief The property of outoutRate
 *  @discussion Currently only support 0 and 1
 */
@property (assign, nonatomic) int filterIndex;

/**
 *  @brief Before recording start when you give a time to check sensor storage status. Unit is minute.
 */
@property (copy, nonatomic) void (^getStorageStatusWithTime)(NSUInteger time);

/**
 *  @brief Constructor with a peripheral
 *  @param peripheral CBPeripheral object
 */
+ (instancetype)deviceWithPeripheral:(CBPeripheral *)peripheral;

/**
 *  @brief Parse BLE advertisement data
 *  @param advertisementData Advertisement data
 */
- (void)parseAdvertisementData:(NSDictionary *)advertisementData;

/**
 *  @brief Parse mac address
 *  @param macAddressData Mac address data
 */
- (void)parseMacAddress:(NSData *)macAddressData;

/**
 *  @brief Judge the XsensDotDevice object if it's equal
 *  @param object The XsensDotDevice object
 */
- (BOOL)isEqual:(XsensDotDevice *)object;

/**
 *  @brief The current bluetooth state
 */
- (CBPeripheralState)state;

/**
 *  @brief The flag that BLE is connected
 */
- (BOOL)stateIsConnected;

/**
 *  @brief The flag that the connection is initialized
 */
- (BOOL)isInitialized;

/**
 *  @brief The flag that the sensor is synced
 */
- (BOOL)isSynced;

/**
 *  @brief The peripheral name
 */
- (NSString *)peripheralName;

/**
 *  @brief The tag name
 */
- (NSString *)displayName;

/**
 *  @brief The mac address
 */
- (NSString *)displayAddress;

/**
 *  @brief The support filter profile list
 */
- (NSArray <XsensDotFilterProfile *> *) filterProfilesList;

@end


/**
    Instruction method
 */
@interface XsensDotDevice (Instruction)
/**
 *  @brief The plotting(real-time streaming) data block, after set plotMeasureEnable = YES, this will outout plotData
 *  @param block Return the XsensDotPlotData data
 */
- (void)setDidParsePlotDataBlock:(void (^ _Nullable)(XsensDotPlotData * _Nonnull plotData))block;

/**
 *  @brief The statistics info block.
 *  @param block Return the XsensDotStatisticsInfo object
 */
- (void)setDidParseStatisticsInfoBlock:(void(^ _Nullable)(XsensDotStatisticsInfo * _Nonnull statisticsInfo))block;
/**
 *  @brief Set the sensor tag name
 *  @param name The tag name
 */
- (void)setDeviceName:(NSString *)name;

/**
 *  @brief Start identifying
 */
- (void)startIdentifying;

/**
 *  @brief Power off the sensor
 */
- (void)powerOff;

/**
 *  @brief Read statistics info
 */
- (void)readStatisticsInfo;

/**
 *  @brief The flat of support statistics feature
 */
- (BOOL)statisticsFeatureEnable;

/**
 *  @brief The block when sensor did power off
 *  @param block The return block
 */
- (void)setDidPowerOffBlock:(void(^ _Nullable)(void))block;

/**
 *  @brief Set the outputRate and filterIndex
 *  @param outputRate outputRate
 *  @param filterIndex filterIndex
 */
- (void)setOutputRate:(int)outputRate filterIndex:(int)filterIndex;

/**
 *  @brief Read the  sensor signal strength
 *  @param block Return block after read the RSSI
 *  @discussion After read the RSSI the @propertity RSSI will also be updated
 */
- (void)readRSSI:(void (^_Nullable)(NSNumber *signal))block;

/**
 *  @brief Start MFM
 */
- (void)startMfm;

/**
 *  @brief Stop MFM
 *  @return The mtb file path
 */
- (NSString *)stopMfm;

/**
 *  @brief Write mtb data to firmware
 *  @param mfmData The mtb data
 */
- (void)writeMfmResult:(NSData *)mfmData;

/**
 *  @brief Set the progress block when start mfm
 *  @param block The block from mfm data parse
 */
- (void)setDidMFMProgress:(void (^_Nullable)(NSString *address, int progress))block;

/**
 *  @brief Set the result block when  mfm has been done
 *  @param block The block from mfm process done
 */
- (void)setDidMFMResult:(void (^_Nullable)(NSString *address, XSDotMFMResultTpye type))block;

/**
 *  @brief  Start firmeare update
 *  @param file The firmeware file
 */
- (void)setFirmwareUpdate:(NSString *)file;

/**
 *  @brief Set power saving time
 *  @param xMinutes The advertisement minutes
 *  @param xSeconds The advertisement seconds
 *  @param yMinutes The connection minutes
 *  @param ySeconds The connection seconds
 */
- (void)setPowerSavingTimeout:(UInt8) xMinutes xSecond:(UInt8)xSeconds yMinutes:(UInt8)yMinutes ySeconds:(UInt8)ySeconds;

/**
 *  @brief Start heading reset
 */
- (void)startHeadingReset;

/**
 *  @brief Start heading revert
 */
- (void)startHeadingRevert;

/**
 *  @brief Read Rot local block
 *  @param block Return block
 */
- (void)setDidreadRotLocal:(void (^_Nullable)(float * _Nonnull rotLocal))block;

/**
 *  @brief Dump crash data
 */
- (void)dumpCrashInfoData;

/**
 *  @brief Clear crash data
 *  @discussion clearCrashInfoData is 150ms later then dumpCrashInfoData  .
 */
- (void)clearCrashInfoData;

/**
 *  @brief Start synchronization
 *  @param address The sensor macAddress
 *  @param type The sync type
 */
- (void)startSync:(NSString *)address type:(UInt8)type;

/**
 *  @brief Stop Synchronization
 */
- (void)stopSync;

/**
 *  @brief Get Recording Status, after call this method the recording.recordingStatus will be update
 */
- (void)getRecordingStatus;

/**
 *  @brief Start recording
 *  @param recordingTime The recording time that you want
 *  @discussion If no clear time, please set it to 0xFFFF, the recording will always do until storage is full
 */
- (void)startRecording:(UInt16)recordingTime;

/**
 *  @brief Stop recording
 */
- (void)stopRecording;

/**
 *  @brief Get sensor flash information, after called it will be initializing totalSpace and usedSpace
 */
- (void)getFlashInfo;

/**
 *  @brief The  getFlashInfo done block
 *  @param block The XSFlashInfoStatus object
 */
- (void)setFlashInfoDoneBlock:(void (^_Nullable)(XSFlashInfoStatus status))block;

/**
 *  @brief If recording.recordingStatus == XSRecordingIsRecording ,and  will be get the
 *          recording.recordingDate, recording.recordingTime ,recording.remainingTime
 */
- (void)getRecordingTime;

/**
 *  @brief Earse recording Data
 */
- (void)eraseData;

/**
 *  @brief The eraseData done block
 *  @param block Return the success result
 */
- (void)setEraseDataDoneBlock:(void (^_Nullable)(int success))block;

/**
 *  @brief Get the export file information , this will be initialize RecordingFile.timeStamap
 */
- (void)getExportFileInfo;

/**
 *  @brief The getExportFileInfo done block
 *  @param block Return the success result
 */
- (void)setExportFileInfoDone:(void (^_Nullable)(BOOL success))block;

/**
 *  @brief Start export recording file data, when call this method, Please ensure two prerequisites
 *          1. set device.exportDataFormat
 *          2. set recording.exportFileList
 *          recording export status in this block:
 *          recording.updateExportingStatus
 */
- (void)startExportFileData;

/**
 *  @brief Stop export recording file data, Recording export status in this block: recording.updateExportingStatus
 */
- (void)stopExportFileData;

/**
 *  @brief The block of startExportFileData
 *  @param block Return the XsensDotPlotData object
 */
- (void)setDidParseExportFileDataBlock:(void (^ _Nullable)(XsensDotPlotData * _Nonnull plotData))block;

/**
 *  @brief Button callback block
 *  @param block The timestamp block
 */
- (void)setDidButtonCallbackBlock:(void (^ _Nullable)(int timestamp))block;

@end

NS_ASSUME_NONNULL_END
