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

@interface XsensDotSyncManager : NSObject

typedef void(^XsensDotSyncResultBolck)(NSArray *syncResult);

/// Start synchronization
/// @param devices  list of XsensDotDevice (the firstObject is the root dot others are scanner)
/// @param resultBlock sync result array have macAddress and the result.
+ (void)startSync:(NSArray<XsensDotDevice *> *)devices result:(XsensDotSyncResultBolck) resultBlock;

/// Add device to sync devices after startSync
/// @param device XsensDotDevice
/// @param status sync status 0x00 : success ,others are fail
/// @param sampleCounter For root node, the sampleCnt is 0, For scan node, the sampleCnt is 0 if failure reason is SynchorizationResult_Unstarted(0x9).
+ (void)addSyncDevice:(XsensDotDevice *)device status:(NSUInteger)status sampleCounter:(UInt32)sampleCounter;

/// Check if sync started.
+ (BOOL)canSync;

+ (void)stopSync:(NSArray<XsensDotDevice *> *)devices;

@end

NS_ASSUME_NONNULL_END
