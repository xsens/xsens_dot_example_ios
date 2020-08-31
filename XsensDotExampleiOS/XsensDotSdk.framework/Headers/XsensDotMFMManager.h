//
//  XsensDotMFMManager.h
//  XsensDotSdk
//
//  Created by Jayson on 2020/5/22.
//  Copyright © 2020 Xsens. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "XsensDotDevice.h"

/*
 The result after mfm has done. (called by XsensDotMFMManager stopMFM)
 */
typedef NS_ENUM(NSUInteger, XSDotMFMResultTpye)
{
    XSDotMFMResultFailed = 0,
    XSDotMFMResultBad,
    XSDotMFMResultAcceptable,
    XSDotMFMResultGood,
};

@protocol XsensDotMFMDelegate <NSObject>
@optional
- (void)onMFMCompleted:(XSDotMFMResultTpye) type;
@end

NS_ASSUME_NONNULL_BEGIN

@interface XsensDotMFMManager : NSObject

@property (assign, nonatomic) XSDotMFMResultTpye resultValue;
@property (weak, nonatomic) id<XsensDotMFMDelegate> mfmDelegate;

@property (readonly, strong, class) XsensDotMFMManager *defaultManager;

- (void)startMFM:(XsensDotDevice *)device;
- (void)stopMFM:(XsensDotDevice *)device;
- (void)writeMFMResult:(XsensDotDevice *)device;

@end

NS_ASSUME_NONNULL_END
