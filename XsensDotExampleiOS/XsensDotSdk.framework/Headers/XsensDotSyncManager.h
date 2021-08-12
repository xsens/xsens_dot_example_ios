//
//  XsensDotSyncManager.h
//  XsensDotSdk
//
//  Created by Jayson on 2020/8/7.
//  Copyright © 2020 Xsens. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "XsensDotDevice.h"

NS_ASSUME_NONNULL_BEGIN

typedef void(^XsensDotSyncResultBolck)(NSArray *syncResult);

/**
 * This class is the synchronization manager. All sensors will be time-synced with each other to a common time base after synchronization.
 * Refer to section 3.3.4 in Xsens DOT User Manual for more information. The root node in the iOS SDK is always the first sensor connected.
 * It will take the sensors about 10 seconds to finish the sync period, so you can reconnect the sensors after that.
 */
@interface XsensDotSyncManager : NSObject

/**
 * Start synchronization
 * @param devices  List of Xsens DOT sensor (the firstObject is the root  others are scanners)
 * @param resultBlock Sync result array have macAddress and the sync result.
 * @discussion The result example :
 *              (
 *              {
 *              address = "D4:CA:6E:F1:6C:0B";
 *              doneSuccess = 1;
 *              sampleCounter = 0;
 *              status = 0;
 *              success = 1; //
 *              }
 *              )
 *              doneSuccess: sync done status, sampleCounter:sync sample counter, status: sync status code, success: the sync success flag 1 is success and 0  is fail
 *
 * @return If firmware support sync feature this will be YES, otherwise it's NO
 */
+ (BOOL)startSync:(NSArray<XsensDotDevice *> *)devices result:(XsensDotSyncResultBolck) resultBlock;


/**
 * Add sensor to sync sensors after startSync (Used in SDK)
 * @param device XsensDotDevice
 * @param status sync status 0x00 : success ,others are fail
 * @param sampleCounter For root node, the sampleCnt is 0, For scan node, the sampleCnt is 0 if failure reason is SynchorizationResult_Unstarted(0x9).
 */
+ (void)addSyncDevice:(XsensDotDevice *)device status:(NSUInteger)status sampleCounter:(UInt32)sampleCounter;

/**
 * Check if sync started.
 * @return The started flag.
 */
+ (BOOL)canSync;

/**
 * Stop synchronization
 * After do it , you can check device.isSynced to get current sync status.
 * @param devices  list of XsensDotDevice
 */
+ (void)stopSync:(NSArray<XsensDotDevice *> *)devices;

@end

NS_ASSUME_NONNULL_END
