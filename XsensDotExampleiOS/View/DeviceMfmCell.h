//
//  DeviceMfmCell.h
//  Xsens DOT
//
//  Created by admin on 2020/9/15.
//  Copyright © 2020 Xsens. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <XsensDotSdk/XsensDotDevice.h>

NS_ASSUME_NONNULL_BEGIN

@interface DeviceMfmCell : UITableViewCell

@property (strong, nonatomic) XsensDotDevice *device;

- (void)cellInProgress:(int)progress;
- (void)cellFinished;
- (void)cellStopped;
- (void)cellDisconnected;
- (void)cellFailed;

+ (NSString *)cellIdentifier;
+ (CGFloat)cellHeight;

@end

NS_ASSUME_NONNULL_END
