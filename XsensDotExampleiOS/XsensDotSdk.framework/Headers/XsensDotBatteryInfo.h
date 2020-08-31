//
//  XsensDotBatteryInfo.h
//  XsensDotSdk
//
//  Created by Nick Yang on 2019/5/13.
//  Copyright © 2019 Xsens. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface XsensDotBatteryInfo : NSObject

/*
    Return the current charging state
 */
@property (assign, nonatomic) BOOL chargeState;
@property (assign, nonatomic) NSInteger value;
+ (instancetype)infoWithChargeState:(BOOL)chargeState value:(NSInteger)value;
- (NSString *)description;

@end

NS_ASSUME_NONNULL_END
