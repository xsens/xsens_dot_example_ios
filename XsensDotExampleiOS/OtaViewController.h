//
//  OtaViewController.h
//  XsensDotExampleiOS
//
//  Created by admin on 2021/7/7.
//  Copyright © 2021 Xsens. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <XsensDotSdk/XsensDotDevice.h>

NS_ASSUME_NONNULL_BEGIN

@interface OtaViewController : UIViewController

@property (strong, nonatomic) XsensDotDevice *device;

@end

NS_ASSUME_NONNULL_END
