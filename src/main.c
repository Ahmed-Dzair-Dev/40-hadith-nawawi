#include <gtk/gtk.h>
#include <json-c/json.h>

typedef struct {
    GtkWidget *window;
    GtkWidget *hadith_view;
    GtkWidget *description_view;
    GtkWidget *hadith_number_label;
    json_object *hadith_array;
    int current_hadith;
} HadithViewer;

static void load_json_file(HadithViewer *viewer) {
    json_object *root = json_object_from_file("40-hadith-nawawi.json");
    if (root) {
        viewer->hadith_array = root;
    }
}

static void update_display(HadithViewer *viewer) {
    if (!viewer->hadith_array) return;

    json_object *hadith = json_object_array_get_idx(viewer->hadith_array, viewer->current_hadith);
    if (!hadith) return;

    json_object *description;
    json_object_object_get_ex(hadith, "description", &description);

    char number[32];
    snprintf(number, sizeof(number), "Hadith #%d", viewer->current_hadith + 1);
    
    gtk_label_set_text(GTK_LABEL(viewer->hadith_number_label), number);
    gtk_text_buffer_set_text(
        gtk_text_view_get_buffer(GTK_TEXT_VIEW(viewer->description_view)),
        json_object_get_string(description),
        -1
    );
}

static void next_hadith(GtkWidget *widget, HadithViewer *viewer) {
    if (viewer->current_hadith < json_object_array_length(viewer->hadith_array) - 1) {
        viewer->current_hadith++;
        update_display(viewer);
    }
}

static void prev_hadith(GtkWidget *widget, HadithViewer *viewer) {
    if (viewer->current_hadith > 0) {
        viewer->current_hadith--;
        update_display(viewer);
    }
}

static void apply_custom_font(GtkWidget *widget) {
    PangoFontDescription *font_desc;
    // TODO: Replace path with your Arabic font path
    font_desc = pango_font_description_from_string("font/KFGQPC Uthmanic Script HAFS Regular.otf");
    gtk_widget_override_font(widget, font_desc);
    pango_font_description_free(font_desc);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    HadithViewer viewer = {
        .current_hadith = 0,
        .hadith_array = NULL
    };

    // Create main window
    viewer.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(viewer.window), "40 Hadith Nawawi");
    gtk_window_set_default_size(GTK_WINDOW(viewer.window), 800, 600);
    g_signal_connect(viewer.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create main vertical box
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(viewer.window), vbox);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);

    // Create header
    viewer.hadith_number_label = gtk_label_new("");
    gtk_box_pack_start(GTK_BOX(vbox), viewer.hadith_number_label, FALSE, FALSE, 0);

    // Create navigation buttons
    GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), button_box, FALSE, FALSE, 0);

    GtkWidget *prev_button = gtk_button_new_with_label("Previous");
    GtkWidget *next_button = gtk_button_new_with_label("Next");
    
    gtk_box_pack_start(GTK_BOX(button_box), prev_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(button_box), next_button, FALSE, FALSE, 0);

    g_signal_connect(prev_button, "clicked", G_CALLBACK(prev_hadith), &viewer);
    g_signal_connect(next_button, "clicked", G_CALLBACK(next_hadith), &viewer);

    // Create scrolled window for description
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                 GTK_POLICY_AUTOMATIC,
                                 GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);

    // Create text view for description
    viewer.description_view = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(viewer.description_view), GTK_WRAP_WORD);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(viewer.description_view), FALSE);
    gtk_container_add(GTK_CONTAINER(scrolled_window), viewer.description_view);

    // Apply custom Arabic font
    apply_custom_font(viewer.description_view);

    // Load JSON and display first hadith
    load_json_file(&viewer);
    update_display(&viewer);

    gtk_widget_show_all(viewer.window);
    gtk_main();

    // Cleanup
    if (viewer.hadith_array) {
        json_object_put(viewer.hadith_array);
    }

    return 0;
}
