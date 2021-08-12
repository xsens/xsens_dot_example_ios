//
//  XsensDotOtaManager.h
//  XsensDotSdk
//
//  Created by Jayson on 2020/3/25.
//  Copyright © 2020 Xsens. All rights reserved.
//

/**
 * The OTA control manager
 */
#import <Foundation/Foundation.h>
#import <XsensDotSdk/XsensDotDevice.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * The XsensDotManager delegate that can update all the status during the whole OTA process
 */
@protocol XsesnDotOtaManagerDelegate <NSObject>
@optional
/**
 * When call  checkOtaRollback or checkOtaRollbackAndDownload this method will be triggered.
 * @param address The XsensDotDevice mac address
 * @param result The rollback result
 * @param version The firmeare version
 * @param releaseNotes The firmware release notes
 */
- (void)onOtaRollback:(NSString *)address result:(BOOL)result version:(NSString *)version releaseNotes:(NSString *)releaseNotes;

/**
 * When call  checkOtaUpdates or checkOtaUpdatesAndDownload this method will be triggered.
 * @param address The XsensDotDevice mac address
 * @param result The update result
 * @param version The firmeare version
 * @param releaseNotes The firmware release notes
 */
- (void)onOtaUpdates:(NSString *)address result:(BOOL)result version:(NSString *)version releaseNotes:(NSString *)releaseNotes;

/**
 * When call startOta and the firmware file is not match the DOT, this method will be triggered.
 * @param address  The XsensDotDevice mac address
 */
- (void)onOtaFileMismatch:(NSString *)address;

/**
 * When call startOta and the sensor is not charging , this method will be triggered.
 * @param address  The XsensDotDevice mac address
 */
- (void)onOtaUncharged:(NSString *)address;

/**
 * When call checkOtaRollbackAndDownload or checkOtaUpdatesAndDownload and the firmeare has been downloaded ,this method will be triggered.
 * @param address The XsensDotDevice mac address
 * @param version The firmware version
 */
- (void)onOtaDownload:(NSString *)address version:(NSString *)version;

/**
 * This method will be triggered after call startOta
 * @param address The XsensDotDevice mac address
 * @param result The start result
 * @param errorCode The error code (0 indicate had no errors)
 */
- (void)onOtaStart:(NSString *)address result:(BOOL)result errorCode:(int)errorCode;

/**
 * This method will be triggered after call startOta
 * @param address The XsensDotDevice mac address
 * @param progress The progress while doing OTA
 * @param errorCode The error code (0 indicate had no errors)
 */
- (void)onOtaProgress:(NSString *)address progress:(float)progress errorCode:(int)errorCode;

/**
 * This method will be triggered after OTA finished or call stopOta
 * @param address The XsensDotDevice mac address
 * @param result The OTA finished result
 * @param errorCode The error code (0 indicate had no errors)
 */
- (void)onOtaEnd:(NSString *)address result:(BOOL)result errorCode:(int)errorCode;

@end


/**
 * OTA Manager class , you can use this class to do anything related to OTA
 * @discussion To get a instance you need to use [XsensDotOtaManager defaultManager]
 */
@interface XsensDotOtaManager : NSObject
/**
 * The default manager
 */
@property (readonly, strong, class) XsensDotOtaManager *defaultManager;
/**
 * The OTA file size
 */
@property (assign, nonatomic, readonly) float cacheSize;

/**
 *  Start  OTA process
 *  @discussion Please make sure the DOT has udpate or rollback before call this method
 *  @param device The XsensDotDevice object
 */
- (void)startOta:(XsensDotDevice *)device;

/**
 *  Clear the firmware files in the local folder
 */
- (void)clearCache;

/**
 * Stop the OTA
 */
- (void)stopOta:(XsensDotDevice *)device;

/**
 * Check if there is available file for firmware updating.
 * @param device The XsensDotDevice object
 */
- (void)checkOtaUpdates:(XsensDotDevice *)device;

/**
 * Check if there is available file for firmware rollback.
 * @param device The XsensDotDevice object
 */
- (void)checkOtaRollback:(XsensDotDevice *)device;

/**
 * Check if there is available file for firmware updating and download the mfw upgrade file.
 * @param device The XsensDotDevice object
 */
- (void)checkOtaRollbackAndDownload:(XsensDotDevice *)device;

/**
 * Check if there is available file for firmware rollback and download the mfw downgrade file.
 * @param device The XsensDotDevice object
 */
- (void)checkOtaUpdatesAndDownload:(XsensDotDevice *)device;

/**
 * Set the XsensDotOtaManager delegate
 * @param delegate The XsesnDotOtaManagerDelegate object
 */
+ (void)setOtaManagerDelegate:(nullable id<XsesnDotOtaManagerDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END
