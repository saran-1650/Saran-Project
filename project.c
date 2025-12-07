#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TEACHERS 100
#define NAME_LEN 50
#define QUAL_LEN 50
#define PHONE_LEN 20
#define ADDR_LEN 120

/* parallel arrays */
int   ids[MAX_TEACHERS];
char  names[MAX_TEACHERS][NAME_LEN];
int   ages[MAX_TEACHERS];
char  quals[MAX_TEACHERS][QUAL_LEN];
char  phones[MAX_TEACHERS][PHONE_LEN];
char  addrs[MAX_TEACHERS][ADDR_LEN];
int   count = 0;

const char *DB_FILE = "teachers_db.txt";

/* ---------- helpers ---------- */
void trim_newline(char *s) {
    size_t n = strlen(s);
    if (n && s[n-1] == '\n') s[n-1] = '\0';
}

void read_line(const char *prompt, char *buf, size_t sz) {
    printf("%s", prompt);
    if (fgets(buf, (int)sz, stdin) == NULL) { buf[0] = '\0'; return; }
    trim_newline(buf);
    /* Replace any '|' to avoid breaking the file format */
    for (size_t i = 0; buf[i]; i++) if (buf[i] == '|') buf[i] = '/';
}

int read_int(const char *prompt) {
    char line[64];
    int v;
    while (1) {
        printf("%s", prompt);
        if (!fgets(line, sizeof(line), stdin)) return 0;
        trim_newline(line);
        int ok = 0;
        for (int i = 0; line[i]; i++) if (line[i] >= '0' && line[i] <= '9') { ok = 1; break; }
        if (ok) { v = atoi(line); return v; }
        printf("Invalid number. Try again.\n");
    }
}

int find_index_by_id(int id) {
    for (int i = 0; i < count; i++) if (ids[i] == id) return i;
    return -1;
}

/* ---------- persistence ---------- */
void save_data(void) {
    FILE *fp = fopen(DB_FILE, "w");
    if (!fp) {
        perror("Could not open database file for writing");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d|%s|%d|%s|%s|%s\n",
                ids[i], names[i], ages[i], quals[i], phones[i], addrs[i]);
    }
    fclose(fp);
}

void load_data(void) {
    FILE *fp = fopen(DB_FILE, "r");
    if (!fp) {
        /* No file yet on first run—this is fine */
        return;
    }
    char line[512];
    while (fgets(line, sizeof(line), fp)) {
        trim_newline(line);
        if (count >= MAX_TEACHERS) break;

        /* tokenize by '|' */
        char *p = line;
        char *tok;
        int field = 0;

        /* Temporary holders */
        int id = 0, age = 0;
        char name[NAME_LEN] = "", qual[QUAL_LEN] = "", phone[PHONE_LEN] = "", addr[ADDR_LEN] = "";

        tok = strtok(p, "|");
        while (tok && field < 6) {
            if (field == 0) id = atoi(tok);
            else if (field == 1) { strncpy(name, tok, NAME_LEN); name[NAME_LEN-1] = '\0'; }
            else if (field == 2) age = atoi(tok);
            else if (field == 3) { strncpy(qual, tok, QUAL_LEN); qual[QUAL_LEN-1] = '\0'; }
            else if (field == 4) { strncpy(phone, tok, PHONE_LEN); phone[PHONE_LEN-1] = '\0'; }
            else if (field == 5) { strncpy(addr, tok, ADDR_LEN); addr[ADDR_LEN-1] = '\0'; }
            field++;
            tok = strtok(NULL, "|");
        }

        if (field == 6) {
            ids[count] = id;
            ages[count] = age;
            strncpy(names[count], name, NAME_LEN); names[count][NAME_LEN-1] = '\0';
            strncpy(quals[count], qual, QUAL_LEN); quals[count][QUAL_LEN-1] = '\0';
            strncpy(phones[count], phone, PHONE_LEN); phones[count][PHONE_LEN-1] = '\0';
            strncpy(addrs[count], addr, ADDR_LEN); addrs[count][ADDR_LEN-1] = '\0';
            count++;
        }
    }
    fclose(fp);
}

/* ---------- main ---------- */
int main(void) {
    load_data();  /* load existing records if present */

    while (1) {
        printf("\n1) Create a new teacher profile\n");
        printf("2) Update the teacher profile by ID\n");
        printf("3) Delete the teacher profile by ID\n");
        printf("4) View the current teachers list\n");
        printf("5) Exit\n");

        int choice = read_int("Enter your choice (1-5): ");

        if (choice == 1) {
            if (count >= MAX_TEACHERS) {
                printf("List is full. Cannot add more teachers.\n");
                continue;
            }

            char name[NAME_LEN], qual[QUAL_LEN], phone[PHONE_LEN], addr[ADDR_LEN];
            int age, id;

            read_line("Enter the name: ", name, sizeof(name));
            age = read_int("Enter the age: ");
            read_line("Enter the qualification: ", qual, sizeof(qual));
            read_line("Enter the phone number: ", phone, sizeof(phone));
            read_line("Enter the address: ", addr, sizeof(addr));
            id = read_int("Enter the ID: ");

            if (find_index_by_id(id) != -1) {
                printf("A teacher with ID %d already exists. Use option 2 to update.\n", id);
                continue;
            }

            ids[count] = id;
            ages[count] = age;
            strncpy(names[count], name, NAME_LEN); names[count][NAME_LEN-1] = '\0';
            strncpy(quals[count], qual, QUAL_LEN); quals[count][QUAL_LEN-1] = '\0';
            strncpy(phones[count], phone, PHONE_LEN); phones[count][PHONE_LEN-1] = '\0';
            strncpy(addrs[count], addr, ADDR_LEN); addrs[count][ADDR_LEN-1] = '\0';
            count++;

            save_data();
            printf("Teacher profile created successfully.\n");
        }
        else if (choice == 2) {
            if (count == 0) { printf("No teachers to update.\n"); continue; }

            int id = read_int("Enter the ID to update: ");
            int idx = find_index_by_id(id);
            if (idx == -1) {
                printf("No teacher found with ID %d.\n", id);
                continue;
            }

            while (1) {
                printf("\nWhat would you like to update?\n");
                printf("1) Name\n");
                printf("2) Age\n");
                printf("3) Qualification\n");
                printf("4) Phone number\n");
                printf("5) Address\n");
                printf("6) Done\n");
                int c = read_int("Enter your choice (1-6): ");

                if (c == 1) {
                    read_line("Enter new name: ", names[idx], NAME_LEN);
                    printf("Name updated.\n");
                } else if (c == 2) {
                    ages[idx] = read_int("Enter new age: ");
                    printf("Age updated.\n");
                } else if (c == 3) {
                    read_line("Enter new qualification: ", quals[idx], QUAL_LEN);
                    printf("Qualification updated.\n");
                } else if (c == 4) {
                    read_line("Enter new phone number: ", phones[idx], PHONE_LEN);
                    printf("Phone number updated.\n");
                } else if (c == 5) {
                    read_line("Enter new address: ", addrs[idx], ADDR_LEN);
                    printf("Address updated.\n");
                } else if (c == 6) {
                    printf("Update finished.\n");
                    break;
                } else {
                    printf("Invalid choice. Try again.\n");
                }
            }
            save_data(); /* persist updates */
        }
        else if (choice == 3) {
            if (count == 0) { printf("No teachers to delete.\n"); continue; }

            int id = read_int("Enter the ID to delete: ");
            int idx = find_index_by_id(id);
            if (idx == -1) {
                printf("No teacher found with ID %d.\n", id);
                continue;
            }

            for (int i = idx; i < count - 1; i++) {
                ids[i] = ids[i+1];
                ages[i] = ages[i+1];
                strncpy(names[i], names[i+1], NAME_LEN);
                strncpy(quals[i], quals[i+1], QUAL_LEN);
                strncpy(phones[i], phones[i+1], PHONE_LEN);
                strncpy(addrs[i], addrs[i+1], ADDR_LEN);
            }
            count--;
            save_data();
            printf("Teacher with ID %d deleted successfully.\n", id);
        }
        else if (choice == 4) {
            if (count == 0) {
                printf("No teachers found.\n");
            } else {
                printf("\n----- Current Teachers List -----\n");
                for (int i = 0; i < count; i++) {
                    printf("ID: %d\n", ids[i]);
                    printf("Name: %s\n", names[i]);
                    printf("Age: %d\n", ages[i]);
                    printf("Qualification: %s\n", quals[i]);
                    printf("Phone: %s\n", phones[i]);
                    printf("Address: %s\n", addrs[i]);
                    printf("---------------------------------\n");
                }
            }
        }
        else if (choice == 5) {
            printf("Thank you!\n");
            break;
        }
        else {
            printf("Invalid choice. Please select between 1 and 5.\n");
        }
    }
    return 0;
}