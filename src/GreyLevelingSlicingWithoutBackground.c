#include <stdio.h>
#include <stdlib.h>
int main() {
    // Declare image variables
    char str[100];
    int width, height, max_color;
    unsigned char *image;
    printf("Enter the name of the file (with .ppm) :");
    gets(str);
    
    int low,high;
    printf("Enter the Lower Limit: ");
    scanf("%d",&low);
    printf("Enter the Higher Limit: ");
    scanf("%d",&high);

    // Read image from file
    FILE *in_file = fopen(str, "rb");
    fscanf(in_file, "P6\n%d %d\n%d\n", &width, &height, &max_color);
    image = (unsigned char *) malloc(width * height * 3);
    fread(image, 1, width * height * 3, in_file);
    fclose(in_file);
    
    
    // Convert to grayscale
    for (int i = 0; i < width * height * 3; i += 3) {
        int avg = (0.299*image[i] + 0.587*image[i + 1] + 0.114*image[i + 2]);
        image[i] = avg;
        image[i + 1] = avg;
        image[i + 2] = avg;
    }
        
    // Grey Level Slicing Without Background
    for (int i = 0; i < width * height * 3; i++) {
        if(image[i]>=low && image[i]<=high)
        {image[i]=255;}
        else
        {image[i]=0;}
    }

    // Write grayscale image to file
    FILE *out_file = fopen("../assets/output_withoutB.ppm", "wb");
    fprintf(out_file, "P6\n%d %d\n%d\n", width, height, max_color);
    fwrite(image, 1, width * height * 3, out_file);
    fclose(out_file);
    free(image);
    return 0;
}
