//
//  MfmViewController.h
//  XsensDotExampleiOS
//
//  Created by Jayson on 2021/11/30.
//  Copyright © 2021 Xsens. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <XsensDotSdk/XsensDotDevice.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, XSDeviceMFMState)
{
    XSDeviceMFMStateDefault = 0,
    XSDeviceMFMStateStart,
    XSDeviceMFMStateProcessing,
    XSDeviceMFMStateComplete
};

@interface MfmViewController : UIViewController

@property (strong, nonatomic) NSArray<XsensDotDevice *> *mfmDevices;

@end

NS_ASSUME_NONNULL_END
