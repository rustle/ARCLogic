##ARCLogic
===

* HASARC - Shorthand version of `__has_feature(objc_arc)`
* HASWEAK - Shorthand version of `__has_feature(objc_arc_weak)`
* STRONG - Expands to strong for ARC and retain for non ARC (useful for property declarations)

* `__STRONG` - Expands to `__strong` for ARC and to nothing for non ARC (useful for variable declarations)
* WEAK - Expands to weak for ARC, assign for non ARC and unsafe\_unretained for ARC without weak support (useful for property declarations)
* `__WEAK` - Expands to `__weak` for ARC, to nothing for non ARC environments and to `__unsafe_unretained` for ARC without weak support (useful for variable declarations)
* `IF_ARC(ARCBlock, NOARCBlock)` - Function style macro for larger blocks of code that are different in ARC
* `NO_ARC(NoARCBlock)` - Function style macro for code that only executes when ARC isn't available
* `NO_WEAK(NoWeakBlock)` - Function style macro for code that only executes when ARC isn't available or doesn't support weak (iOS 4, OS X 10.6)

###Example

<pre>
@interface Foo : NSObject
@property (WEAK, nonatomic) id delegate;
@property (STRONG, nonatomic) id observer;
@end

@implementation
@synthesize delegate=_delegate;
@synthesize observer=_observer;
- (void)dealloc
{
	[[NSNotificationCenter defaultCenter] removeObserver:_observer];
	NO_ARC(
		[_observer release];
		[super dealloc];
	)
}
- (id)init
{
	self = [super init];
	if (self)
	{
		// __block was a weak reference pre ARC, but is now a 
		__WEAK __block __typeof__(self) bSelf = self;
		self.observer = 
		[[NSNotificationCenter defaultCenter] addObserverForName:UIApplicationWillDoSomething object:nil queue:[NSOperationQueue mainQueue] usingBlock:^(NSNotification *note) {
			NSLog(@"This is me: %@", bSelf);
		}];
	}
	return self;
}
@end

@interface Bar : NSObject
@property (STRONG, nonatomic) Foo *foo;
@end

@implementation Bar
@synthesize foo=_foo;
- (void)dealloc
{
	NO_WEAK(
		_foo.delegate = nil;
	)
	NO_ARC(
		[_foo release];
		[super dealloc];
	)
}
- (id)init
{
	self = [super init];
	if (self)
	{
		_foo = [Foo new];
		_foo.delegate = self;
	}
	return self;
}
@end
</pre>

Use and enjoy and provide feedback.

-----------

[FMDB](https://github.com/ccgus/fmdb/blob/master/src/FMDatabase.h) covers very similar ground using a set of macros that wrap retain/release/autorelease.