# xsens_dot_example_iOS

## Get start
1. git clone https://github.com/xsens/xsens_dot_example_ios
2. pod install
3. open XsensDotExampleiOS.xcworkspace
4. Please use a real iPhone to run with the sample code , the simulator will appear errors.

## Main methods
* Scan sensors

1. Set the delegate
```
[XsensDotConnectionManager setConnectionDelegate:self]; 
```
2. Start scan
```
@property (strong, nonatomic) NSMutableArray<XsensDotDevice *> *deviceList;
```
```
[XsensDotConnectionManager scan];
```
```
- (void)onDiscoverDevice:(XsensDotDevice *)device
{
    NSInteger index = [self.deviceList indexOfObject:device];
    if(index == NSNotFound)
    {
        [self.deviceList addObject:device];
    }
}
```
* Connect a sensor

```
XsensDotDevice *device = self.deviceList.firstObject;
[XsensDotConnectionManager connect:device];
```

* Synchronization

```
XsensDotSyncResultBolck block = ^(NSArray *array)
    {

    };
[XsensDotSyncManager startSync:self.deviceList result:block];
```

* Measurement

```
XsensDotDevice *device = self.deviceList.firstObject;
device.plotMeasureMode = XSBleDevicePayloadCompleteEuler;
device.plotMeasureEnable = YES;
```

## For more details, please visit : https://www.xsens.com/developer


