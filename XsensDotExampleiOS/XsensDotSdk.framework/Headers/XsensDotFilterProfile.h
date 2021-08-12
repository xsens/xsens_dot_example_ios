//
//  XsensDotFilterProfile.h
//  XsensDotSdk
//
//  Created by admin on 2020/11/26.
//  Copyright © 2020 Xsens. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  The Xsens DOT filter profile class.
 */
@interface XsensDotFilterProfile : NSObject

/**
 *  The filter profile index
 *  @discussion We currently have two types of index: 0 and 1
 */
- (UInt8)filterIndex;
/**
 *  The filter profile name
 *  @discussion We currently have two types of name: "General" and "Dynamic"
 */
- (NSString *)filterName;

/**
 *  Constructor method
 *  @param name The filter profile name
 *  @param index The filter profile index
 */
- (instancetype)initWithName:(NSString *)name index:(UInt8)index;

@end

NS_ASSUME_NONNULL_END
