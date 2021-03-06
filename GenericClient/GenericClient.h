#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class Future;

typedef NS_ENUM(NSInteger, RequestParameterEncodingType)
{
  RequestParameterEncodingTypeJSON,
  RequestParameterEncodingTypeForm,
  RequestParameterEncodingTypeCustom
};

@interface ClientResponse : NSObject <NSCopying>

@property (copy, nonatomic, readonly) NSURLRequest* originalRequest;
@property (copy, nonatomic, readonly) NSHTTPURLResponse* HTTPResponse;
@property (copy, nonatomic, readonly) NSData* output;

+ (ClientResponse*)withOriginalRequest:(NSURLRequest*)originalRequest
                          HTTPResponse:(NSHTTPURLResponse*)HTTPResponse
                                output:(NSData*)output;

@end

@interface ClientError : NSObject <NSCopying>

@property (nonatomic, readonly) NSInteger statusCode;
@property (copy, nonatomic, readonly, nullable) NSString* urlString;
@property (copy, nonatomic, readonly, nullable) NSDictionary* requestHeaders;
@property (copy, nonatomic, readonly, nullable) NSDictionary* responseHeaders;
@property (copy, nonatomic, readonly, nullable) NSString* outputString;
@property (copy, nonatomic, readonly, nullable) NSDictionary* serverErrors;
@property (copy, nonatomic, readonly, nullable) NSError* networkError;

@property (nonatomic, readonly) NSError* globalError;

@property (nonatomic, readonly) NSDictionary* keyedDescription;

+ (ClientError*)withStatusCode:(NSInteger)statusCode
                     urlString:(NSString* _Nullable)urlString
                requestHeaders:(NSDictionary* _Nullable)requestHeaders
               responseHeaders:(NSDictionary* _Nullable)responseHeaders
                  outputString:(NSString* _Nullable)outputString
                  serverErrors:(NSDictionary* _Nullable)serverErrors
                  networkError:(NSError* _Nullable)networkError;

+ (ClientError*)withResponse:(ClientResponse*)response
                serverErrors:(NSDictionary* _Nullable)serverErrors
                networkError:(NSError* _Nullable)networkError;

@end

@interface RequestParameterEncoding : NSObject <NSCopying>

@property (nonatomic, readonly) RequestParameterEncodingType type;

+ (RequestParameterEncoding*)JSON;
+ (RequestParameterEncoding*)form;
+ (RequestParameterEncoding*)customWithEncodingBlock:(NSString*(^)(NSDictionary*))customEncodingBlock;

@end

@interface GenericClient : NSObject

@property (copy, nonatomic, readonly) NSString* urlString;

+ (void)setLogActive:(BOOL)logActive;

+ (GenericClient*)withURLString:(NSString*)urlString;
+ (GenericClient*)withURLString:(NSString*)urlString
              parameterEncoding:(RequestParameterEncoding*)parameterEncoding;
+ (GenericClient*)withURLString:(NSString*)urlStirng
			  parameterEncoding:(RequestParameterEncoding*)parameterEncoding
				  customHeaders:(NSDictionary* _Nullable)customHeaders
				   trustedHosts:(NSArray<NSString*>* _Nullable)trustedHosts;

/// Future<ClientResponse,ClientError>
- (Future*)getRequestWithParameters:(NSDictionary* _Nullable)parameters;

/// Future<ClientResponse,ClientError>
- (Future*)postRequestWithParameters:(NSDictionary* _Nullable)parameters;

#pragma mark - utility

+ (NSString*)queryStringFromDict:(NSDictionary*)dict;
+ (NSDictionary*)basicAuthorizationHeaderWithUsername:(NSString*)username
                                             password:(NSString*)password;

@end

NS_ASSUME_NONNULL_END
