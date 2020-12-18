//
//  XsensDotFilterProfile.h
//  XsensDotSdk
//
//  Created by admin on 2020/11/26.
//  Copyright © 2020 Xsens. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface XsensDotFilterProfile : NSObject

- (UInt8)filterIndex;
- (NSString *)filterName;

- (instancetype)initWithName:(NSString *)name index:(UInt8)index;

@end

NS_ASSUME_NONNULL_END
