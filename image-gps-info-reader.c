#include <stdio.h>
#include <stdlib.h>
#include <libexif/exif-data.h>
#include <libexif/exif-utils.h>
#include <libexif/exif-tag.h>

// trim_spaces() and show_tag() function are from libexif/contrib/examples/photographer.c which in public domain by Dan Fandrich

/* Remove spaces on the right of the string */
static void trim_spaces(char *buf) {
    char *s = buf-1;
    for (; *buf; ++buf) {
        if (*buf != ' ')
            s = buf;
    }
    *++s = 0; /* nul terminate the string on the first of the final spaces */
}

static void show_tag(ExifData *d, ExifIfd ifd, ExifTag tag)
{
    /* See if this tag exists */
    ExifEntry *entry = exif_content_get_entry(d->ifd[ifd],tag);
    if (entry) {
        char buf[1024];

        /* Get the contents of the tag in human-readable form */
        exif_entry_get_value(entry, buf, sizeof(buf));

        /* Don't bother printing it if it's entirely blank */
        trim_spaces(buf);
        if (*buf) {
            printf("[%s]: %s\n%s\n\n", exif_tag_get_name_in_ifd(tag,ifd), buf, exif_tag_get_description_in_ifd(tag, ifd));
        }
    }
}



int main(int argc, char **argv) {
    if(argc < 2) {
        fprintf(stderr, "Usage: %s image.jpg\n", argv[0]);
        fprintf(stderr, "Erase GPS info of the image.\n");
        exit(EXIT_FAILURE);
    }
    const char *image_path = argv[1];
    if (image_path != NULL) {        
        //load the image
        ExifData *exifData = exif_data_new_from_file(image_path);
        if(!exifData) {
            fprintf(stderr, "EXIF data might be empty.\n");
            exit(EXIT_FAILURE);
        }
        // now we get the ExifData

        for (int i = EXIF_TAG_GPS_VERSION_ID; i <= EXIF_TAG_GPS_H_POSITIONING_ERROR; i++) {
            show_tag(exifData, EXIF_IFD_GPS, i);
        }
        
        exif_data_unref(exifData);
        exit(EXIT_SUCCESS);
    } else {
        //image_path is null.
        fprintf(stderr, "image_path is null.\n");
        exit(EXIT_FAILURE);
    }
    

    return 0;
}
