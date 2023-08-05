#import <Foundation/Foundation.h>

@interface ObjCExceptions : NSObject

+ (BOOL)catch:(void(^)(void))tryBlock error:(__autoreleasing NSError **)error;

@end
