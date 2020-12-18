//
//  XsensDotReconnectManager.h
//  XsensDotSdk
//
//  Created by Nick Yang on 2019/6/19.
//  Copyright © 2019 Xsens. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface XsensDotReconnectManager : NSObject

+ (void)setEnable:(BOOL)enable;
+ (BOOL)enable;
+ (void)setHandUp:(BOOL)enable;
+ (void)onManagerStateUpdated;
+ (void)onBoundDeviceCapacityModified;

@end

NS_ASSUME_NONNULL_END
