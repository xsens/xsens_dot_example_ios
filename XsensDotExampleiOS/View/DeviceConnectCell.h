//
//  DeviceConnectCell.h
//  XsensDotDebug
//
//  Created by Jayson on 2020/6/5.
//  Copyright © 2020 Xsens. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class XsensDotDevice;

@interface DeviceConnectCell : UITableViewCell

@property (strong, nonatomic) XsensDotDevice *device;
@property (copy, nonatomic) void (^connectAction)(DeviceConnectCell *cell);

- (void)refreshDeviceStatus;

+ (NSString *)cellIdentifier;
+ (CGFloat)cellHeight;

@end

NS_ASSUME_NONNULL_END
