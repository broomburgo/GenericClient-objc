
#import <Foundation/Foundation.h>

@interface ExceptionEntity : NSObject

@property (copy, nonatomic, readonly) NSException* __nonnull exception;
@property (copy, nonatomic, readonly) NSArray* __nullable tags;
@property (copy, nonatomic, readonly) NSDictionary* __nullable info;

+ (ExceptionEntity* __nonnull)withException:(NSException* __nonnull)exception;
+ (ExceptionEntity* __nonnull)withException:(NSException* __nonnull)exception tags:(NSArray* __nullable)tags;
+ (ExceptionEntity* __nonnull)withException:(NSException* __nonnull)exception tags:(NSArray* __nullable)tags info:(NSDictionary* __nullable)info;

@end