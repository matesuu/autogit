/*

Note: For the sake of simplicity, the name of a remote repository when initialized will always be 'origin'. As this is a tool
aimed to simplify the use of git as a tool, there are no current plans to change this design facet. Therefore, autogit only supports
the use of a singular remote. Will work on this later...

p.s. nettspend sucks

- matesuu

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>

/* ─────────────────────────────────────────────
   HOME SCREEN  –  pulsating sphere + "autogit"
   ───────────────────────────────────────────── */

/* Sphere geometry */
#define SPH_RADIUS   8          /* character-cell radius          */
#define SPH_COLS     (SPH_RADIUS * 2 + 1)
#define SPH_ROWS     (SPH_RADIUS + 1)   /* half-height (aspect ratio fix) */
#define PULSE_FRAMES 36         /* frames per full pulse cycle     */
#define PULSE_LOOPS  3          /* how many times the pulse repeats*/
#define FRAME_US     55000      /* microseconds per frame (~18 fps)*/

/* ANSI helpers */
#define ANSI_RESET       "\033[0m"
#define ANSI_BOLD        "\033[1m"
#define ANSI_HIDE_CURSOR "\033[?25l"
#define ANSI_SHOW_CURSOR "\033[?25h"
#define ANSI_CLEAR       "\033[2J\033[H"

/* Move cursor to row r, col c (1-indexed) */
static void move_to(int r, int c) { printf("\033[%d;%dH", r, c); }

/* RGB true-colour foreground */
static void rgb_fg(int r, int g, int b) { printf("\033[38;2;%d;%d;%dm", r, g, b); }

/* ---------- render one frame ----------
 *  pulse  : 0.0 … 1.0  (sine-wave driven glow intensity)
 *  origin_row / origin_col : top-left of the sphere block (1-indexed)
 */
static void render_sphere(int origin_row, int origin_col, double pulse)
{
    /* shade characters from dim centre to bright edge */
    static const char shades[] = " .:;+=xX$#";
    int   n_shades = (int)(sizeof(shades) - 1);

    /* light direction (top-left) */
    double lx = -0.6, ly = -0.6, lz = 0.5;
    double llen = sqrt(lx*lx + ly*ly + lz*lz);
    lx /= llen; ly /= llen; lz /= llen;

    double R = (double)SPH_RADIUS;

    for (int row = 0; row < SPH_ROWS * 2; row++) {
        move_to(origin_row + row, origin_col);

        /* map row to y in [-R, R], compressed for aspect ratio */
        double y = ((double)(SPH_ROWS - 1) - row * 0.5) / (SPH_ROWS - 1) * R;

        for (int col = 0; col < SPH_COLS; col++) {
            double x = ((double)col - R) / R * R;

            double dist2 = x*x + y*y;
            if (dist2 > R * R) {
                /* outside sphere — print blank */
                printf(" ");
                continue;
            }

            double z   = sqrt(R * R - dist2);
            /* surface normal */
            double nx  = x / R, ny = y / R, nz = z / R;
            double diff = nx*lx + ny*ly + nz*lz;
            if (diff < 0.0) diff = 0.0;

            /* ambient + diffuse */
            double light = 0.15 + 0.85 * diff;

            /* pulsating glow: boost brightness with pulse */
            double glow = light + 0.35 * pulse * (1.0 - dist2 / (R * R));
            if (glow > 1.0) glow = 1.0;

            /* colour: deep violet core → electric cyan edge (Amp palette) */
            double t    = dist2 / (R * R);          /* 0=centre, 1=edge  */
            int cr = (int)(( 80 + 120 * (1.0-t)) * glow);
            int cg = (int)((  0 + 200 * (1.0-t) + 55 * t) * glow);
            int cb = (int)((200 + 55  * (1.0-t)) * glow);
            if (cr > 255) cr = 255;
            if (cg > 255) cg = 255;
            if (cb > 255) cb = 255;

            int shade_idx = (int)(glow * (n_shades - 1));
            if (shade_idx >= n_shades) shade_idx = n_shades - 1;

            rgb_fg(cr, cg, cb);
            printf("%c", shades[shade_idx]);
        }
    }
}

/* ---------- render "autogit" wordmark ---------- */
static void render_wordmark(int origin_row, int origin_col, double pulse)
{
    /* Glow: white-blue base, flares brighter on pulse peak */
    double glow = 0.75 + 0.25 * pulse;
    int r = (int)(180 * glow);
    int g = (int)(200 * glow);
    int b = 255;
    if (r > 255) r = 255;
    if (g > 255) g = 255;

    /* Large block-letter "autogit" rendered as 5-row ASCII art */
    static const char *letters[] = {
        /* row 0 */ " █████╗ ██╗   ██╗████████╗ ██████╗  ██████╗ ██╗████████╗",
        /* row 1 */ "██╔══██╗██║   ██║╚══██╔══╝██╔═══██╗██╔════╝ ██║╚══██╔══╝",
        /* row 2 */ "███████║██║   ██║   ██║   ██║   ██║██║  ███╗██║   ██║   ",
        /* row 3 */ "██╔══██║██║   ██║   ██║   ██║   ██║██║   ██║██║   ██║   ",
        /* row 4 */ "██║  ██║╚██████╔╝   ██║   ╚██████╔╝╚██████╔╝██║   ██║   ",
        /* row 5 */ "╚═╝  ╚═╝ ╚═════╝    ╚═╝    ╚═════╝  ╚═════╝ ╚═╝   ╚═╝   ",
    };
    int n_rows = 6;

    for (int i = 0; i < n_rows; i++) {
        move_to(origin_row + i, origin_col);
        rgb_fg(r, g, b);
        printf("%s", letters[i]);
    }
}

/* ---------- public entry point ---------- */
void home_screen(void)
{
    printf(ANSI_HIDE_CURSOR);
    printf(ANSI_CLEAR);
    fflush(stdout);

    int sphere_top  = 4;   /* row where sphere starts    */
    int sphere_left = 4;   /* col where sphere starts    */

    /* wordmark sits vertically centred beside sphere */
    int word_top  = sphere_top + SPH_ROWS - 2;   /* vertically centred */
    int word_left = sphere_left + SPH_COLS + 4;  /* right of sphere    */

    int total_frames = PULSE_FRAMES * PULSE_LOOPS;

    for (int frame = 0; frame < total_frames; frame++) {
        double angle = (double)frame / PULSE_FRAMES * 2.0 * M_PI;
        double pulse = 0.5 + 0.5 * sin(angle);   /* 0.0 … 1.0 */

        render_sphere(sphere_top, sphere_left, pulse);
        render_wordmark(word_top, word_left, pulse);

        /* subtitle line below wordmark */
        move_to(word_top + 7, word_left);
        double sub_glow = 0.5 + 0.3 * pulse;
        rgb_fg((int)(120 * sub_glow), (int)(160 * sub_glow), (int)(220 * sub_glow));
        printf("a git automation utility");

        /* version tag */
        move_to(word_top + 9, word_left);
        rgb_fg(80, 100, 140);
        printf("v1.0  –  type 'autogit help' to get started");

        printf(ANSI_RESET);
        fflush(stdout);
        usleep(FRAME_US);
    }

    /* settle on final frame with full glow */
    render_sphere(sphere_top, sphere_left, 1.0);
    render_wordmark(word_top, word_left, 1.0);

    move_to(word_top + 7, word_left);
    rgb_fg(120, 160, 220);
    printf("a git automation utility");

    move_to(word_top + 9, word_left);
    rgb_fg(80, 100, 140);
    printf("v1.0  –  type 'autogit help' to get started");

    /* move cursor below everything before returning */
    move_to(sphere_top + SPH_ROWS * 2 + 3, 1);
    printf(ANSI_RESET);
    printf(ANSI_SHOW_CURSOR);
    fflush(stdout);
}

int run_git_command(char* GIT_COMMAND, char** GIT_COMMAND_ARGUMENTS)
{
    pid_t PARENT_ID = fork();

    if(PARENT_ID < 0)
    {
        perror("error: could not create child process");
        
        exit(1);
    }


    if(PARENT_ID == 0)
    {
        execvp(GIT_COMMAND, GIT_COMMAND_ARGUMENTS);

        perror("error: could not execute child process");
        
        exit(1);
    }

    else
    {
        int status = 0;
        waitpid(PARENT_ID, &status, 0);

        if(!WIFEXITED(status))
        {
            exit(1);
        }
    }

    return 0;
}

void help()
{
    printf("\nautogit v.1 - a git automation utility");
    printf("\n\nhelp - \n\n");
    printf("init - initialize a local and remote repository and create branch main - autogit init <remote_url_name> \n");
    printf("deinit - remove currently existing remote - autogit deinit \n");
    printf("info - display current information of current remotes and branches - autogit info \n");
    printf("new - creates a new branch within remote - autogit new <branch_name> \n");
    printf("switch - changes current working branch - autogit change <branch_name> \n");
    printf("delete - deletes a given branch from remote - autogit delete <branch_name> \n");
    printf("push - push all current changes to a specified branch - autogit push <branch_name> <optional: commit message> \n");
    printf("pull - pull all current changes from a specified branch - autogit pull <branch_name> \n");
    printf("rebase - rebase a given branch (usually for your initial commit) - autogit rebase <branch_name> \n\n");

    printf("written by matesuu (December 2024) \n\n");
}

int init(char* REMOTE_URL)
{
    char* args_0[] = {"git", "init", NULL};
    run_git_command("git", args_0);

    char* args_1[] = {"git", "init", "&&", "git", "symbolic-ref", "HEAD", "refs/heads/main", NULL};
    run_git_command("git", args_1);

    char* args_2[] = {"git", "config", "--global", "init.defaultBranch", "main", NULL};
    run_git_command("git", args_2);

    char* args_3[] = {"git", "remote", "add", "origin", REMOTE_URL, NULL};
    run_git_command("git", args_3);

    char* args_4[] = {"git", "remote", "-v", NULL};
    run_git_command("git", args_4);

    printf("successfully initialized and added remote repository ");

    return 0;
}

int forget()
{
    char* args_1[] = {"git", "remote", "remove", "origin", NULL};
    run_git_command("git", args_1);

    return 0;
}

int info()
{
    char* args_1[] = {"git", "remote", "-v", NULL};
    run_git_command("git", args_1);

    char* args_2[] = {"git", "branch", NULL};
    run_git_command("git", args_2);

    return 0;
}

int new(char* BRANCH_NAME)
{
    char* args_1[] = {"git", "checkout", "-b", BRANCH_NAME, NULL};
    run_git_command("git", args_1);

    return 0;
}

int change(char* BRANCH_NAME)
{
    char* args_1[] = {"git", "checkout", BRANCH_NAME, NULL};
    run_git_command("git", args_1);

    return 0;
}

int rebase(char* BRANCH_NAME)
{
    char* args_0[] = {"git", "pull", "--rebase", "origin", BRANCH_NAME, NULL};
    run_git_command("git", args_0);

    return 0;
}

int delete(char* BRANCH_NAME)
{
    char* args_1[] = {"git", "branch", "-d", BRANCH_NAME, NULL};
    run_git_command("git", args_1);

    return 0;
}

int push(char* BRANCH_NAME)
{
    char* args_1[] = {"git", "status", NULL};
    run_git_command("git", args_1);

    char* args_2[] = {"git", "add", ".", "--all", NULL};
    run_git_command("git", args_2);

    char* args_3[] = {"git", "commit", "-m", "commited to repo using autogit", NULL};
    run_git_command("git", args_3);

    char* args_5[] = {"git", "push", "-u", "origin", BRANCH_NAME, NULL};
    run_git_command("git", args_5);

    return 0;
}

int push_commit(char* BRANCH_NAME, char* COMMIT_MESSAGE)
{
    char* args_1[] = {"git", "status", NULL};
    run_git_command("git", args_1);

    char* args_2[] = {"git", "add", ".", "--all", NULL};
    run_git_command("git", args_2);

    char* args_3[] = {"git", "commit", "-m", COMMIT_MESSAGE, NULL};
    run_git_command("git", args_3);

    char* args_5[] = {"git", "push", "-u", "origin", BRANCH_NAME, NULL};
    run_git_command("git", args_5);

    return 0;
}

int pull(char* BRANCH_NAME)
{
    char* args_1[] = {"git", "status", NULL};
    run_git_command("git", args_1);

    char* args_2[] = {"git", "pull", "origin", BRANCH_NAME, NULL};
    run_git_command("git", args_2);

    return 0;
}
