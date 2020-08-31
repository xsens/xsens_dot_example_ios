//
//  XsensDotUpdateManager.h
//  XsensDotSdk
//
//  Created by Jayson on 2020/3/25.
//  Copyright © 2020 Xsens. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "XsensDotDevice.h"
#import "XsensDotUpdatePacket.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, XsensDotUpdateState)
{
    XsensDotUpdateStateDownloading = 0,
    XsensDotUpdateStateUpdating,
    XsensDotUpdateStateDownloadFailed,
    XsensDotUpdateStateUpdateFailed
};

typedef NS_ENUM(NSUInteger, XSDotUpdateOptions)
{
    XSDotUpdateUpgrade = 0,
    XSDotUpdateDowngrade,
};

@protocol XsensDotUpdateDelegate <NSObject>
@optional
- (void)onUpdateStatus:(XsensDotUpdateState) type;
- (void)onUpdateCompleted:(XsensDotUpdatePacket *)updatePacket;
@end

typedef void(^XSDotUpdateDeviceResponseSuccessBlock)(NSDictionary *responseObject);

typedef void(^XSDotUpdateDevicesResponseSuccessBlock)(NSArray *responseObject);

typedef void(^XSDotUpdateResponseFailBlock)(NSError *error);

typedef void(^XSDotDownloadResultBlock)(BOOL result);


@interface XsensDotUpdateManager : NSObject

@property (readonly, strong, class) XsensDotUpdateManager *defaultManager;
@property (assign, nonatomic, readonly) float cacheSize;
@property (weak, nonatomic) id<XsensDotUpdateDelegate> updateDelegate;

/*
    This API for multi-devices update.
 */
- (void)checkUpdateForDevices:(NSArray<XsensDotDevice *> *)devices
                      success:(XSDotUpdateDevicesResponseSuccessBlock)successBlock
                         fail:(XSDotUpdateResponseFailBlock)failBlock
                      options:(XSDotUpdateOptions) options;

/*
    This API for single device update.
*/
- (void)checkUpdateForDevice:(XsensDotDevice *)device
                     success:(XSDotUpdateDeviceResponseSuccessBlock)successBlock
                        fail:(XSDotUpdateResponseFailBlock)failBlock
                     options:(XSDotUpdateOptions) options;

/*
    start OTA
 */
- (void)startUpdate:(XsensDotDevice *)device;

/*
  Clear cache 
 */
- (void)clearCache;

@end

NS_ASSUME_NONNULL_END
