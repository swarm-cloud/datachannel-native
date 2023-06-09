// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from libdc.djinni

#import "DCReliabilityType.h"
#import <Foundation/Foundation.h>

@interface DCReliability : NSObject
- (nonnull instancetype)init NS_UNAVAILABLE;
+ (nonnull instancetype)new NS_UNAVAILABLE;
- (nonnull instancetype)initWithType:(DCReliabilityType)type
                           unordered:(BOOL)unordered
                            rexmitMs:(int64_t)rexmitMs NS_DESIGNATED_INITIALIZER;
+ (nonnull instancetype)ReliabilityWithType:(DCReliabilityType)type
                                  unordered:(BOOL)unordered
                                   rexmitMs:(int64_t)rexmitMs;

@property (nonatomic, readonly) DCReliabilityType type;

@property (nonatomic, readonly) BOOL unordered;

@property (nonatomic, readonly) int64_t rexmitMs;

@end
