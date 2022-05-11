public class exo4 {

    static {
		System.loadLibrary("exo4");
	}

    public static native int getPid();
    public static native long pfork();
    public static native void pexit(int n);
    public static native int psleep(int n);
    public static native int pwait();


    public static int EXIT_FAILURE = 1;
	public static int EXIT_SUCCESS = 0;
	public static int NB_FORK = 10;
	public static int NB_FOR = 10;

    public static void main(String[] args) {
		for (int i = 0; i < exo4.NB_FORK; i++) {
			var pids = new long[10];
            if ((pids[i] = pfork()) < 0) {
                System.err.println("Error: fork");
                pexit(EXIT_FAILURE);
            } else if (pids[i] == 0) {
                for (int j = 0; j < NB_FOR; j++) {
                    System.out.print("Current child process ID: " + getPid() + ", result: "+ i + "\n");
                    psleep(2);
                }
                exo4.pexit(exo4.EXIT_SUCCESS);
            } else {
            	continue;
            }
        }
        while (pwait() != -1);
		for (int k = 0; k < NB_FORK; k++) {
			int pid = pwait();
			if (pid == -1) {
				System.err.println("Error: Child exited with non-zero status.\n");
				pexit(EXIT_FAILURE);
			}
	        System.out.println("Waited for a child to finish\n");
	    }


    }

}
