import java.lang.management.ManagementFactory;

public class exo3 {

    static {
		System.loadLibrary("exo3");
	}

    public static native int getPid();
    public static native void createFork();

    public static void main(String[] args) {
        long pid = ProcessHandle.current().pid();
        String pidFactory = ManagementFactory.getRuntimeMXBean().getName().split("@")[0];
        System.out.println(pid);
        System.out.println(pidFactory);

        System.out.println(exo3.getPid());
        exo3.createFork();
    }

}
