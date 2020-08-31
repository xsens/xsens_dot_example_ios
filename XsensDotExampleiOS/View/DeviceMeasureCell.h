//
//  DeviceMeasureCell.h
//  XsensDotExampleiOS
//
//  Created by Jayson on 2020/8/26.
//  Copyright © 2020 Xsens. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <XsensDotSdk/XsensDotDevice.h>

NS_ASSUME_NONNULL_BEGIN

@interface DeviceMeasureCell : UITableViewCell

@property (strong, nonatomic) XsensDotDevice *device;

+ (NSString *)cellIdentifier;
+ (CGFloat)cellHeight;

@end

NS_ASSUME_NONNULL_END
