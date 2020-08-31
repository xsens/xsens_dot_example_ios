//
//  XsensDotConnectionManager.h
//  XsensDotSdk
//
//  Created by Nick Yang on 2019/5/15.
//  Copyright © 2019 Xsens. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "XsensDotDevice.h"
#import "XsensDotDefine.h"

@protocol XsensDotConnectionDelegate <NSObject>
@optional
- (void)onManagerStateUpdate:(XSDotManagerState)managerState;
- (void)onScanCompleted;
- (void)onDiscoverDevice:(XsensDotDevice *_Nonnull)device;
- (void)onDeviceConnectSucceeded:(XsensDotDevice *_Nonnull)device;
- (void)onDeviceConnectFailed:(XsensDotDevice *_Nonnull)device;
- (void)onDeviceDisconnected:(XsensDotDevice *_Nonnull)device;
@end


NS_ASSUME_NONNULL_BEGIN

@interface XsensDotConnectionManager : NSObject

+ (void)setConnectionDelegate:(nullable id<XsensDotConnectionDelegate>)delegate;
+ (XSDotManagerState)managerState;
+ (BOOL)managerStateIsPoweredOn;
+ (void)scan;
+ (void)stopScan;
+ (void)connect:(XsensDotDevice *)device;
+ (void)disconnect:(XsensDotDevice *)device;

@end

NS_ASSUME_NONNULL_END
