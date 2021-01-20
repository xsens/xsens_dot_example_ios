//
//  XsensDotOtaSimpleManager.h
//  XsensDotSdk
//
//  Created by Jayson on 2020/10/27.
//  Copyright © 2020 Xsens. All rights reserved.
//



#import <Foundation/Foundation.h>
#import "XsensDotDevice.h"

NS_ASSUME_NONNULL_BEGIN


typedef void(^XSDotOtaDeviceResonponseSuccessBlock)(NSString *address, BOOL hasNewFirmwareVersion, int requestCode);

typedef void(^XSDotOtaDeviceResponseFailBlock)(NSError *error);

/**
 *  The Xsens DOT simple OTA manager ,and it can check firmware update.
 */
@interface XsensDotOtaSimpleManager : NSObject

/**
    @brief Returns the default singleton instance.
*/
@property (readonly, strong, class) XsensDotOtaSimpleManager *defaultManager;

/**
    @brief Check firmware ota update
 
    @param device XsensDotDevice object
    @param successBlock Return block if check success
    @param failBlock Return block if check fail
    @param requestCode The request code
 */
- (void)checkOtaUpdates:(XsensDotDevice *)device
                     success:(XSDotOtaDeviceResonponseSuccessBlock)successBlock
                        fail:(XSDotOtaDeviceResponseFailBlock)failBlock
                        requestCode:(int)requestCode;

@end

NS_ASSUME_NONNULL_END
