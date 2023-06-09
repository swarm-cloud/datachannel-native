// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from libdc.djinni

#import "DCReliability.h"
#import <Foundation/Foundation.h>

@interface DCDataChannelInit : NSObject
- (nonnull instancetype)init NS_UNAVAILABLE;
+ (nonnull instancetype)new NS_UNAVAILABLE;
- (nonnull instancetype)initWithReliability:(nonnull DCReliability *)reliability
                                 negotiated:(BOOL)negotiated
                                         id:(nullable NSNumber *)id
                                   protocol:(nonnull NSString *)protocol NS_DESIGNATED_INITIALIZER;
+ (nonnull instancetype)DataChannelInitWithReliability:(nonnull DCReliability *)reliability
                                            negotiated:(BOOL)negotiated
                                                    id:(nullable NSNumber *)id
                                              protocol:(nonnull NSString *)protocol;

@property (nonatomic, readonly, nonnull) DCReliability * reliability;

@property (nonatomic, readonly) BOOL negotiated;

@property (nonatomic, readonly, nullable) NSNumber * id;

@property (nonatomic, readonly, nonnull) NSString * protocol;

@end
