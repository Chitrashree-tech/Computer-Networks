#include <stdio.h>
#include <string.h>

int main() {
    char rem[50], a[50], s[50], c, msg[50], gen[30];
    int i, genlen, t, j, flag = 0, k, n;

    printf("Enter the generator polynomial: ");
    gets(gen);

    printf("Generator polynomial (CRC): %s\n", gen);
    genlen = strlen(gen);
    k = genlen - 1;

    printf("Enter the message: ");
    n = 0;
    while ((c = getchar()) != '\n' && c != EOF)
        msg[n++] = c;
    msg[n] = '\0';

    // Append k zeros to message
    for (i = 0; i < n; i++)
        a[i] = msg[i];
    for (i = 0; i < k; i++)
        a[n + i] = '0';
    a[n + k] = '\0';

    printf("\nMessage polynomial appended with zeros:\n");
    puts(a);

    // Division (mod 2)
    for (i = 0; i < n; i++) {
        if (a[i] == '1') {
            t = i;
            for (j = 0; j <= k; j++) {
                if (a[t] == gen[j])
                    a[t] = '0';
                else
                    a[t] = '1';
                t++;
            }
        }
    }

    // Get remainder
    for (i = 0; i < k; i++)
        rem[i] = a[n + i];
    rem[k] = '\0';

    printf("\nThe checksum (remainder): ");
    puts(rem);

    // Message + checksum
    printf("\nTransmitted message with checksum:\n");
    for (i = 0; i < n; i++)
        a[i] = msg[i];
    for (i = 0; i < k; i++)
        a[n + i] = rem[i];
    a[n + k] = '\0';
    puts(a);

    // Receiver side
    printf("\nEnter the received message: ");
    n = 0;
    while ((c = getchar()) != '\n' && c != EOF)
        s[n++] = c;
    s[n] = '\0';

    // Division at receiver
    for (i = 0; i < n - k; i++) {
        if (s[i] == '1') {
            t = i;
            for (j = 0; j <= k; j++, t++) {
                if (s[t] == gen[j])
                    s[t] = '0';
                else
                    s[t] = '1';
            }
        }
    }

    // Check remainder
    for (i = 0; i < k; i++)
        rem[i] = s[n - k + i];
    rem[k] = '\0';

    flag = 0;
    for (i = 0; i < k; i++) {
        if (rem[i] == '1')
            flag = 1;
    }

    if (flag == 0)
        printf("\n✅ Received message is error-free.\n");
    else
        printf("\n❌ Error detected in received message.\n");

    return 0;
}
