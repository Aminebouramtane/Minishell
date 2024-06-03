

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>

// char* expand_env_vars(const char *input) {
//     size_t input_len = strlen(input);
//     size_t output_size = input_len + 1;
//     char *output = malloc(output_size);
//     if (!output) {
//         return NULL;
//     }
//     output[0] = '\0';

//     const char *env_var_start;
//     const char *env_var_end;
//     size_t len_before_var;

//     while ((env_var_start = strchr(input, '$')) != NULL) {
//         // Append the part before the environment variable
//         len_before_var = env_var_start - input;
//         strncat(output, input, len_before_var);

//         // Find the end of the environment variable name
//         env_var_end = env_var_start + 1;
//         while (*env_var_end && (isalnum(*env_var_end) || *env_var_end == '_')) {
//             env_var_end++;
//         }

//         // Get the environment variable name
//         size_t env_var_len = env_var_end - (env_var_start + 1);
//         char env_var_name[env_var_len + 1];
//         strncpy(env_var_name, env_var_start + 1, env_var_len);
//         env_var_name[env_var_len] = '\0';

//         // Get the environment variable value
//         char *value = getenv(env_var_name);
//         if (value) {
//             // Calculate new output size and reallocate if necessary
//             size_t new_output_size = strlen(output) + strlen(value) + 1;
//             if (new_output_size > output_size) {
//                 output_size = new_output_size;
//                 output = realloc(output, output_size);
//                 if (!output) {
//                     return NULL; // Reallocation failed
//                 }
//             }
//             strcat(output, value);
//         }

//         // Move the input pointer past the environment variable
//         input = env_var_end;
//     }

//     // Append the remaining part of the input string
//     strcat(output, input);

//     return output;
// }


// int main() {
//     char input[] = "hello my name is $USER fffff";
//     char *expanded_str = expand_env_vars(input);

//     if (expanded_str) {
//         printf("%s\n", expanded_str);
//         free(expanded_str);
//     } else {
//         printf("Error expanding environment variables.\n");
//     }

//     return 0;
// }
