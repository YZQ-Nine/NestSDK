//
//  PicoNestSDK.h
//  PicoNestSDK
//
//  Created by Charles.Yao on 2017/7/4.
//  Copyright © 2017年 com.pico. All rights reserved.
//

#import <Foundation/Foundation.h>

//TODO:正式版注销
extern NSString *const PicoNestPostResultKey;

/**
 统计的场景类别，默认为普通统计；若使用游戏统计API，则需选择游戏场景类别，如E_PVR_GAME。
 */
typedef NS_ENUM (NSUInteger, PVREtype) {
    
    E_PVR_NORMAL = 0,    // default value
    E_PVR_GAME = 1,      // game
};

#define NestConfigInstance [PVRNestConfigInstance shared]
@interface PVRNestConfigInstance : NSObject
/** required:  appkey string */
@property (nonatomic, copy) NSString *appkey;
/** optional:  default: "App Store"*/
@property (nonatomic, copy) NSString *channel;
/** optional:  default: E_PVR_NORMAL */
@property (nonatomic, assign) PVREtype E_PVR_ETYPE;

+ (PVRNestConfigInstance *)shared;

@end

@interface PicoNestSDK : NSObject


/**
 初始化Nest统计模块
 @param configure PVRNestConfigInstance 实例类，具体参照该类成员的参数定义
 */
+ (void)startWithConfigure:(PVRNestConfigInstance *)configure;

/**
 停用Nest统计模块
 */
+ (void)stop;

///---------------------------------------------------------------------------------------
/// @name  设置
///---------------------------------------------------------------------------------------

/** 开启CrashReport收集, 默认YES(开启状态).
 @param value 设置为NO,可关闭CrashReport收集功能.
 */
+ (void)setCrashReportEnabled:(BOOL)value;

/** 设置是否打印sdk的log信息, 默认NO(不打印log).
 @param value 设置为YES, SDK 会输出log信息可供调试参考. 除非特殊需要，否则发布产品时需改回NO.
 */
+ (void)setLogEnabled:(BOOL)value;

/** 设定log发送间隔
 @param second 单位为秒,最小90秒,最大86400秒(24hour).
 */
+ (void)setLogSendInterval:(double)second;


#pragma mark event logs
///---------------------------------------------------------------------------------------
/// @name  页面计时
///---------------------------------------------------------------------------------------

/** 自动页面时长统计, 开始记录某个页面展示时长.
 使用方法：必须配对调用beginLogPageView:和endLogPageView:两个函数来完成自动统计，若只调用某一个函数不会生成有效数据。
 在该页面展示时调用beginLogPageView:，当退出该页面时调用endLogPageView:
 @param pageName 统计的页面名称.
 */
+ (void)beginLogPageView:(NSString *)pageName;

/** 自动页面时长统计, 结束记录某个页面展示时长.
 使用方法：必须配对调用beginLogPageView:和endLogPageView:两个函数来完成自动统计，若只调用某一个函数不会生成有效数据。
 在该页面展示时调用beginLogPageView:，当退出该页面时调用endLogPageView:
 @param pageName 统计的页面名称.
 */
+ (void)endLogPageView:(NSString *)pageName;


///---------------------------------------------------------------------------------------
/// @name  计数事件统计
///---------------------------------------------------------------------------------------

/** 自定义事件,数量统计.
 @param  event_id 事件Id.
 */
+ (void)event:(NSString *)event_id;

/** 自定义事件,数量统计.
 @param  event_id 事件Id.
 @param  value 分类标签。不同的标签会分别进行统计，方便同一事件的不同标签的对比,为nil或空字符串时后台会生成和eventId同名的标签.
 */
+ (void)event:(NSString *)event_id value:(NSString *)value; // value为nil或@""时，等同于 event:event_id value:event_id;

/** 自定义事件,数量统计.
 @param  event_id 事件Id.
 @param  number 数值
 */
+ (void)event:(NSString *)event_id number:(long)number;
/** 自定义事件,数量统计.
 @param  event_id 事件Id.
 @param  value 分类标签。不同的标签会分别进行统计，方便同一事件的不同标签的对比,为nil或空字符串时后台会生成和eventId同名的标签.
 */
+ (void)event:(NSString *)event_id value:(NSString *)value number:(long)number; // value为nil或@""时，等同于 event:event_id value:event_id;

/**
 自定义事件,数量统计.
 
 @param event_id 同上
 @param attributes 事件的属性和取值（键值对），不能为空
 */
+ (void)event:(NSString *)event_id attributes:(NSDictionary *)attributes;

+ (void)event:(NSString *)event_id value:(NSString *)value attributes:(NSDictionary *)attributes;

+ (void)event:(NSString *)event_id number:(long)number attributes:(NSDictionary *)attributes;

+ (void)event:(NSString *)event_id value:(NSString *)value number:(long)number attributes:(NSDictionary *)attributes;


#pragma mark - user methods
///---------------------------------------------------------------------------------------
/// @name  自有账号统计
///---------------------------------------------------------------------------------------

/** active user sign-in.
 使用sign-In函数后，如果结束该统计，需要调用sign-Off函数
 @param user_id   : user's ID
 @param user_name : user's name
 @param provider : 不能以下划线"_"开头，使用大写字母和数字标识; 如果是上市公司，建议使用股票代码。
 */
+ (void)statisticalSignInWithUserID:(NSString *)user_id userName:(NSString *)user_name provider:(NSString *)provider;

/** active user sign-off.
 停止sign-in 账号的统计
 */
+ (void)statisticalSignOff;




@end
