//
//  XsensDotMFMManager.h
//  XsensDotSdk
//
//  Created by Jayson on 2020/5/22.
//  Copyright © 2020 Xsens. All rights reserved.
//

/**
 * The XsensDot MFM  manager class
 */
#import <Foundation/Foundation.h>
#import <XsensDotSdk/XsensDotDevice.h>
#import <XsensDotSdk/XsensDotDefine.h>

/**
 * The XsensDotMFMManager's delegate that can update MFM progress and status
 */
@protocol XsensDotMFMDelegate <NSObject>

@optional
/**
 * When call  startMFM  this method will be triggered.
 * @param progress The MFM progress
 * @param address The XsensDotDevice address
 */
- (void)onMFMProgress:(int)progress address:(NSString *_Nullable)address;

/**
 * When  MFM process completed  this method will be triggered.
 * @param type The MFM result satus
 * @param address The XsensDotDevice address
 */
- (void)onMFMCompleted:(XSDotMFMResultTpye) type address:(NSString *_Nullable)address;

@end

NS_ASSUME_NONNULL_BEGIN

@interface XsensDotMFMManager : NSObject

/**
 * The XsensDotMFMDelegate property, set mfmDelegate before call startMFM
 */
@property (weak, nonatomic) id<XsensDotMFMDelegate> mfmDelegate;

/**
 * Get default XsensDotMFMManager object
 */
@property (readonly, strong, class) XsensDotMFMManager *defaultManager;

/**
 * Start MFM
 * @param devices The XsensDotDevice object list
 */
- (void)startMFM:(NSArray <XsensDotDevice *>*)devices;

/**
 * Stop MFM
 * @param devices The XsensDotDevice object list
 */
- (void)stopMFM:(NSArray <XsensDotDevice *>*)devices;

@end

NS_ASSUME_NONNULL_END
