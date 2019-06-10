# polyv-ios-upload-sdk
保利威 iOS 上传 SDK 

## 1. 概述

PLVVodUploadSDK 是广州易方信息科技股份有限公司提供的可集成于项目中用于 iOS 设备上传视频文件到服务器的 SDK，支持断点续传。使用本 SDK 需要在[保利威视频云平台](http://www.polyv.net/)注册账号，并使用该账号进行登录，上传后的视频文件可在该视频平台上进行查看、剪辑、播放、删除等操作。

## 2. 文件目录

PLVVodUploadSDK 的文件目录如下：

![PLVVodUploadSDK 文件目录](https://github.com/polyv/polyv-ios-upload-sdk/blob/master/resource/PLVVodUploadSDK.png)

其中红色虚线方框里的是 SDK 的 public 文件。

## 3. 接入准备

兼容设备：iOS 8.0 以上的 32 位、64 位 iOS 设备

开发环境：Xcode 10.0 以上、CocoaPods 1.5.3 以上

## 4. 开始集成

### 4.1 接入 SDK
##### 安装 CocoaPods

CocoaPods 是 Objective-C的一个依赖管理器，它可以自动化并简化在项目中使用第三方库的过程。你可以用以下命令安装:

```
$ gem install cocoapods
```

##### Podfile

要使用 CocoaPods 将 PLVVodUploadSDK 集成到 Xcode 项目中，需要在您的项目中新建一个 Podfile 文件，并在 Podfile 中指定:

```ruby
source 'https://github.com/CocoaPods/Specs.git'
platform :ios, '8.0'

target 'TargetName' do
pod 'PLVVodUploadSDK', '~> 0.1.0'
end
```

然后，执行如下命令：

```
$ pod install
```


### 4.2 SDK 登录

PLVUploadClient 是进行登录、上传请求的操作类，使用 PLVUploadClient 的方法 "-loginWithUserId:secretKey:" 进行登录，参数 userId、secretKey 可登录 polyv 的[视频云平台](http://www.polyv.net/)获取。

```Objective-C
/**
 SDK 登录
 @param userId 用户 ID
 @param secretKey 用户 secretKey
 */
- (void)loginWithUserId:(NSString *)userId secretKey:(NSString *)secretKey;
```

以在 AppDelegate 中进行 SDK 登录为例，示例代码如下：

```Objective-C
@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    NSString *userId, secretKey; // 初始化为用户自己的 userId、secretKey
    [[PLVUploadClient sharedClient] loginWithUserId:userId secretKey:secretKey];
    ……
}

……
  
@end
```

### 4.3 回调监听

登录成功与否、包括上传过程中的状态变化，都会通过委托代理的方式通知，代理协议是 PLVUploadClientDelegate，PLVUploadClient 支持多代理，允许多个类同时对上传 SDK 的状态变化进行监听。使用 PLVUploadClient 的方法 "-addDelegate:" 新增代理，使用方法 "-removeDelegate:" 移除代理。

```Objective-C
/**
 PLVUploadClient 支持多代理
 添加委托代理
 @param delegate 代理
 */
- (void)addDelegate:(id<PLVUploadClientDelegate>)delegate;

/**
 PLVUploadClient 支持多代理
 移除委托代理
 @param delegate 代理
 */
- (void)removeDelegate:(id<PLVUploadClientDelegate>)delegate;
```

以在一个 UIViewController 对象中进行监听为例：

```objective-c
@interface UIViewController ()<
PLVUploadClientDelegate
>
……
@end
 
@implementation UIViewController
  
- (void)viewDidLoad {
    [super viewDidLoad];
    [[PLVUploadClient sharedClient] addDelegate:self];
    ……
}

- (void)dealloc {
    [[PLVUploadClient sharedClient] removeDelegate:self];
    ……
}

……

@end
```

协议 PLVUploadClientDelegate 包含如下几个代理方法，均为 optional 方法，开发者可按需使用：

```objective-c
/**
 SDK 登录失败
 @param error 失败 error （含错误码和 userInfo ）
 */
- (void)uploadClientLoginError:(NSError *)error;

/**
 初始化上传过程中遇到失败
 @param error 失败 error （含错误码和 userInfo ）
 */
- (void)prepareUploadError:(NSError *)error fileURL:(NSURL *)fileURL;

/**
 启动上传任务失败
 @param vid 失败的视频 vid
 */
- (void)startUploadTaskFailure:(NSString *)vid;

/**
 某一个任务被加入等待队列
 @param video 等待上传的任务（ PLVUploadVideo 对象）
 */
- (void)waitingUploadTask:(PLVUploadVideo *)video;

/**
 开始上传某一个任务
 @param video 开始上传的任务（ PLVUploadVideo 对象）
 */
- (void)startUploadTask:(PLVUploadVideo *)video;

/**
 上传结束
 如果成功，error 为 nil
 @param video 上传结束的任务（ PLVUploadVideo 对象）
 @param error 如果上传失败，回传失败的 NSError 对象指针
 */
- (void)didUploadTask:(PLVUploadVideo *)video error:(NSError * __nullable)error;

/**
 上传任务进度变化
 注意：该方法运行在后台线程，非主线程！
 @param vid 视频 vid
 @param progress 上传进度（大于 0 小于 1）
 */
- (void)uploadTask:(NSString *)vid progressChange:(float)progress;

/**
 所有任务上传结束（包括成功或失败，不包含被中止/中断的任务）
 */
- (void)didAllUploadTaskComplete;
```

如果登录成功不会有任何回调，如果登录失败，会通过代理方法 "-uploadClientLoginError:" 进行通知，登录失败的错误码有如下三种，更详细的错误原因可通过 NSError 对象的 userInfo 属性获知：

- PLVClientErrorCodeLoginFailure：登录失败
- PLVClientErrorCodeAccountError：不得使用公共账号
- PLVClientErrorCodeGetTokenFailure：获取 token 失败

示例代码如下：

```objective-c
@implementation UIViewController

- (void)uploadClientLoginError:(NSError *)error {
    NSLog(@"登录 SDK 失败，失败原因：%@", error.userInfo);
    if (error.code == PLVClientErrorCodeLoginFailure) {
        // 登录失败
    } else if (error.code == PLVClientErrorCodeAccountError) {
        // 不得使用公共账号
    } else if (error.code == PLVClientErrorCodeGetTokenFailure) {
        // 获取 token 失败
    }
}

@end
```

### 4.4 调试日志

通过设置 PLVUploadClient 的属性 enableLog，可用于开启控制台的调试日志，默认 enableLog 为 NO。开启日志代码示例如下：

```objective-c
[PLVUploadClient sharedClient].enableLog = YES;
```

### 4.5 上传视频

##### 4.5.1 上传任务初始化

使用 PLVUploadClient 的方法 "-uploadVideoAtFileURL:" 初始化上传任务，参数 fileURL 是上传文件在本地的存储路径 URL。

```objective-c
@interface PLVUploadClient : NSObject

……
  
/**
 上传视频文件
 @param fileURL 视频文件本地 URL
 @return 如果出错，返回一个 NSError 对象，如果没有，返回 nil
 */
- (NSError *)uploadVideoAtFileURL:(NSURL *)fileURL;

……
  
@end
```

**注意，文件上传之前必须先拷贝到想要集成上传 SDK 的 app 的沙盒文件夹中来，否则会因为 iOS 权限限制而导致无法访问，所以 fileURL 必须是 app 的沙盒文件夹路径。**

如果任务初始化成功，该方法会返回 nil，否则会返回一个 NSError 对象。还可以通过 delegate 的方式获知初始化失败的原因，对应的 delegate 方法是 "-prepareUploadError:fileURL:"。任务初始化失败的错误码有如下三种，更详细的错误原因可通过 NSError 对象的 userInfo 属性获知：

- PLVClientErrorCodeHaventLogin：尚未登录 SDK
- PLVClientErrorCodeNoEnoughSpace：任务初始化失败
- PLVClientErrorCodeNoEnoughSpace：剩余空间不足

delegate 方法的示例代码如下：

```objective-c
- (void)prepareUploadError:(NSError *)error fileURL:(NSURL *)fileURL {
    if (error.code == PLVClientErrorCodeHaventLogin) {
        NSLog(@"尚未登录 SDK");
        NSString *userId, secretKey; // 初始化为用户自己的 userId、secretKey
        [[PLVUploadClient sharedClient] loginWithUserId:userId secretKey:secretKey];
    } else if (error.code == PLVClientErrorCodeNoEnoughSpace) {
        NSLog(@"任务初始化失败：失败原因 %@", error.userInfo); 
    } else if (error.code == PLVClientErrorCodeNoEnoughSpace) {
        NSLog(@"剩余空间不足");
    }
}
```

##### 4.5.2 上传任务队列

上传任务按照初始化的顺序，依次添加到上传任务队列中，任务队列最大并发数为 3，超过并发数的任务会进入等待状态，直到有别的任务完成。通过监听 delegate 方法 "-waitingUploadTask:" 和方法 "-startUploadTask:" 可以知道任务队列的变化：

```objective-c
- (void)waitingUploadTask:(PLVUploadVideo *)video {
    // 上传任务 video 被加入队列中，进入等待状态
}

- (void)startUploadTask:(PLVUploadVideo *)video {
    // 上传任务 video 被加入队列中，准备开始上传
}
```

PLVUploadVideo 是上传任务的数据模型，属性 vid 是 PLVUploadVideo 对象的唯一标识。通过 PLVUploadClient 的方法 "-videoWithVid:" 可获取到上传任务队列中某一个 vid 的 PLVUploadVideo 对象，如果该对象不存在，返回 nil。通过方法 "-allUploadVideos" 可获取到上传任务队列中的所有任务，这两个方法声明如下：

```objective-c
@interface PLVUploadClient : NSObject

……
  
/**
 返回所有上传中或等待上传的任务
 status 为 PLVUploadStatusWaiting, PLVUploadStatusUploading, PLVUploadStatusResumable
 @return 上传任务数组，数组元素为 PLVUploadVideo 对象
 */
- (NSArray <PLVUploadVideo *>*)allUploadVideos;

/**
 在上传中或等待上传的任务队列中，查找指定 vid 的上传任务
 @param vid 上传任务对应的视频 vid
 @return 上传任务（ PLVUploadVideo 对象）
 */
- (PLVUploadVideo *)videoWithVid:(NSString *)vid;

@end
```

##### 4.5.3 上传进度监听

PLVUploadVideo 对象中包含一个 block 属性 uploadProgress，可通过该属性监听每一个上传任务的上传进度。代码示例如下：

```objective-c
PLVUploadVideo *video; // 通过 4.5.2 提到的 delegate 方法返回
video.uploadProgress = ^(float progress) {
  NSLog(@"任务 vid：%@ 的上传进度为 %f", video.vid, progress);
});
```

 也可以通过 delegate 方法 "-uploadTask:progressChange:" 进行监听，示例代码如下：

```objective-c
- (void)uploadTask:(NSString *)vid progressChange:(float)progress {
    NSLog(@"任务 vid：%@ 的上传进度为 %f", vid, progress);
}
```

##### 4.5.4 上传中止或结束

想要中止上传中的任务，可以调用 PLVUploadClient 的方法 "-abortUploadWithVid:"，方法声明如下，调用结束后任务会同步中止，被中止的任务不能恢复，不可再续传，只能通过 4.5.1 的方法重新进行任务初始化。

```objective-c
/**
 中止视频上传
 适用于 status 为 PLVUploadStatusWaiting, PLVUploadStatusUploading 的上传任务
 @param vid 上传任务的 vid
 */
- (void)abortUploadWithVid:(NSString *)vid;
```

上传结束，不管成功、失败还是被中止，都会收到 delegate 方法 "-didUploadTask:error:" 的通知。如果成功，error 为 nil。如果失败，会通过 error 告知失败的类型，上传失败的错误码分为两种，具体的失败原因通过 NSError 对象的 userInfo 属性获知：

- PLVClientErrorCodeOSSErrorCanResumeUpload：可续传
- PLVClientErrorCodeOSSErrorCannotResumeUpload：不可续传

示例代码如下：

```objective-c
- (void)didUploadTask:(PLVUploadVideo *)video error:(NSError *)error {
    if (error) {
        if (error.code == PLVClientErrorCodeOSSErrorCanResumeUpload) {
            NSLog(@"任务 vid：%@ 上传失败（可续传），失败原因 %@", video.vid, error.userInfo);
        } else if (error.code == PLVClientErrorCodeOSSErrorCannotResumeUpload) {
            NSLog(@"任务 vid：%@ 上传失败（不可续传），失败原因 %@", video.vid, error.userInfo);
        }
    } else {
        NSLog(@"任务 vid：%@ 上传成功", video.vid);
    }
}
```

当所有加入队列的上传任务都完成时（成功与失败都算完成），delegate 方法 "-didAllUploadTaskComplete" 会被调用，示例代码如下：

```objective-c
- (void)didAllUploadTaskComplete {
    NSLog(@"所有任务上传结束");
}
```

##### 4.5.5 失败任务续传

上传失败时，如果错误码为 PLVClientErrorCodeOSSErrorCanResumeUpload，可使用 PLVUploadClient 的方法 "-retryUploadWithVid:fileURL:" 进行续传，方法声明如下：

```objective-c
/**
 恢复视频上传
 适用于 status 为 PLVUploadStatusResumable 的上传任务
 @param vid 上传任务的 vid
 @param fileURL 上传文件的 URL
 */
- (void)retryUploadWithVid:(NSString *)vid fileURL:(NSURL *)fileURL;
```

如果续传任务启动成功，会收到 delegate 方法 "-waitingUploadTask:" 或方法 "-startUploadTask:" 的通知，如 4.5.2。如果启动失败，会收到 delegate 方法 "-startUploadTaskFailure:" 通知。

```objective-c
- (void)startUploadTaskFailure:(NSString *)vid {
    NSLog(@"任务 vid：%@ 上传启动失败", vid);
}
```

##### 4.5.6 上传任务状态

综上所述，上传任务包含多种状态，PLVUploadVideo 中的属性 status 的枚举类型声明如下：

```objective-c
/**
 视频上传状态
 - PLVUploadStatusWaiting: 超过最大并发数等待上传中
 - PLVUploadStatusUploading: 上传中
 - PLVUploadStatusResumable: 上传中断，可续传
 - PLVUploadStatusFailure: 上传失败，不可续传
 - PLVUploadStatusAborted: 上传任务被中止，不可续传
 - PLVUploadStatusComplete: 上传成功
 */
typedef NS_ENUM(NSInteger, PLVUploadStatus) {
    PLVUploadStatusWaiting = 0,
    PLVUploadStatusUploading,
    PLVUploadStatusResumable,
    PLVUploadStatusFailure,
    PLVUploadStatusAborted,
    PLVUploadStatusComplete
};

/**
 上传任务模型
 */
@interface PLVUploadVideo : NSObject

……

/**
 视频上传状态
 */
@property (nonatomic, assign) PLVUploadStatus status;

……
  
@end
```

##### 4.5.7 更多上传参数

除了 4.5.1 中提到的 PLVUploadClient 的方法 "-uploadVideoAtFileURL:"，我们还可以使用如下的方法，为上传任务定义更多的参数：

```objective-c
@interface PLVUploadClient : NSObject

……
  
/**
 上传视频文件
 @param uploadParameter 参数封装类（包含更多自定义参数）
 @return 如果出错，返回一个 NSError 对象，如果没有，返回 nil
 */
- (NSError *)uploadVideoWithMutipleParameter:(PLVUploadParameter *)uploadParameter;

……
  
@end
```

其中，参数 uploadParameter 包含了上传任务的多个自定义参数，包括上传到哪个分类目录下，是否录屏、是否保持源文件、视频文件描述、视频文件标签。除了视频文件的本地存储路径是不可为空的属性，其他属性如果不被设置，都有默认值。PLVUploadParameter 类的各个属性声明如下。

```objective-c
/**
 初始化视频上传任务时的参数封装类
 */
@interface PLVUploadParameter : NSObject

/**
 待上传的视频文件的本地存储 URL
 */
@property (nonatomic, strong) NSURL *fileURL;

/**
 上传目录分类 ID，默认为根目录（ID 为 1）
 */
@property (nonatomic, assign) long long catalogId;

/**
 是否录屏，默认为否
 */
@property (nonatomic, assign) BOOL screenRecord;

/**
 是否保持源文件，默认为否
 */
@property (nonatomic, assign) BOOL keepSource;

/**
 待上传的视频文件描述，可选，不传默认为空
 */
@property (nonatomic, copy) NSString * __nullable videoDescription;

/**
 待上传的视频文件标签，可选，不传默认为空
 */
@property (nonatomic, copy) NSString * __nullable videoTag;

@end
```

## 5. 错误码

文件 PLVUploadErrorCodeDefine 定义了所有的错误码，声明如下：

```objective-c
/**
 上传错误码枚举
 */
typedef NS_ENUM (NSInteger, PLVClientErrorCode) {
    PLVClientErrorCodeLoginFailure = 0, // 登录 SDK 失败（userId、secretKey 为空）
    PLVClientErrorCodeAccountError, // 不得使用公共账号进行上传
    PLVClientErrorCodeGetTokenFailure, // 获取 token 失败
    PLVClientErrorCodeHaventLogin, // 尚未登录 SDK
    PLVClientErrorCodeInitUploadTaskFailure, // 初始化上传任务失败
    PLVClientErrorCodeNoEnoughSpace,  // 云空间不足
    PLVClientErrorCodeOSSErrorCanResumeUpload, // 上传失败，可续传
    PLVClientErrorCodeOSSErrorCannotResumeUpload // 上传失败，不可续传
};
```

这些 PLVClientErrorCode 枚举值就是 NSError 对象中的 code 属性。
