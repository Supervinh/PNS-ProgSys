import java.lang.management.ManagementFactory;

public class exo2 {

    static {
		System.loadLibrary("exo2");
	}

    public static native int getPid();

    public static void main(String[] args) {
        long pid = ProcessHandle.current().pid();
        String pidFactory = ManagementFactory.getRuntimeMXBean().getName().split("@")[0];
        System.out.println(pid);
        System.out.println(pidFactory);

        System.out.println(exo2.getPid());
    }
}
