package cool.couplet.rtmvv;

/**
 * Created by whg on 16-1-15.
 */
public class Aefh {
    static {
        System.loadLibrary("aefh");
    }

    static public native Dirent myreaddir(int level);
    static public native Dirent myreadcouplet(int level);
    static public native Dirent myreaddir2(int level);


    // 返回 seek 到的级别
    static public native int myseekdir(String path);

    static public native String mygetcwd();

    static public native int myrewinddir();

}
