//
//  XsensDotBatteryInfo.h
//  XsensDotSdk
//
//  Created by Nick Yang on 2019/5/13.
//  Copyright © 2019 Xsens. All rights reserved.
//

/**
 *  This class has battery information of sensor. Get current battery value and charging state.
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface XsensDotBatteryInfo : NSObject

/**
 *  Charging status property of the sensor, YES is charging, No is not charging
 */
@property (assign, nonatomic, readonly) BOOL chargeState;

/**
 *  Battery value property of the sensor
 */
@property (assign, nonatomic, readonly) NSInteger value;

/**
 * Constructor method
 * @param chargeState Charging state
 * @param value Battery value
 */
+ (instancetype)infoWithChargeState:(BOOL)chargeState value:(NSInteger)value;

/**
 * The Battery description
 * @return Battery description string, the  format is : @"Battery:(Charging, 45%") or @"Battery:(Uncharged, 45%)"
 */
- (NSString *)description;

@end

NS_ASSUME_NONNULL_END
