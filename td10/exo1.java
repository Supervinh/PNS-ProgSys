import java.lang.management.ManagementFactory;

public class exo1 {
    public static void main(String[] args) {
        long pid = ProcessHandle.current().pid();
        String pidFactory = ManagementFactory.getRuntimeMXBean().getName().split("@")[0];
        System.out.println(pid);
        System.out.println(pidFactory);

    }

}
