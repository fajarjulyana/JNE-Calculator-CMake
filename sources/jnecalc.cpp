#include <gtk/gtk.h>

// Struktur untuk menyimpan nilai tambahan panjang, lebar, dan tinggi
typedef struct {
    double tambahan_panjang;
    double tambahan_lebar;
    double tambahan_tinggi;
} TambahanPacking;

static void on_window_closed(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

static void on_hitung_clicked(GtkWidget *widget, gpointer data) {
    // Mengambil nilai dari panjang, lebar, tinggi, harga, tambahan, dan opsi packing
    GtkWidget *panjang_entry = (GtkWidget *)g_object_get_data(G_OBJECT(widget), "panjang_entry");
    GtkWidget *lebar_entry = (GtkWidget *)g_object_get_data(G_OBJECT(widget), "lebar_entry");
    GtkWidget *tinggi_entry = (GtkWidget *)g_object_get_data(G_OBJECT(widget), "tinggi_entry");
    GtkWidget *harga_entry = (GtkWidget *)g_object_get_data(G_OBJECT(widget), "harga_entry");
    GtkWidget *packing_combobox = (GtkWidget *)g_object_get_data(G_OBJECT(widget), "packing_combobox");
    GtkWidget *entry_custom_panjang = (GtkWidget *)g_object_get_data(G_OBJECT(widget), "entry_custom_panjang");
    GtkWidget *entry_custom_lebar = (GtkWidget *)g_object_get_data(G_OBJECT(widget), "entry_custom_lebar");
    GtkWidget *entry_custom_tinggi = (GtkWidget *)g_object_get_data(G_OBJECT(widget), "entry_custom_tinggi");
    GtkWidget *hasil_label = (GtkWidget *)g_object_get_data(G_OBJECT(widget), "hasil_label");

    const char *panjang_str = gtk_entry_get_text(GTK_ENTRY(panjang_entry));
    const char *lebar_str = gtk_entry_get_text(GTK_ENTRY(lebar_entry));
    const char *tinggi_str = gtk_entry_get_text(GTK_ENTRY(tinggi_entry));
    const char *harga_str = gtk_entry_get_text(GTK_ENTRY(harga_entry));

    // Mengkonversi nilai menjadi tipe numerik
    double panjang = atof(panjang_str);
    double lebar = atof(lebar_str);
    double tinggi = atof(tinggi_str);
    double harga = atof(harga_str);

    // Mendapatkan nilai pilihan dari ComboBox
    GtkTreeIter iter;
    GtkTreeModel *model = gtk_combo_box_get_model(GTK_COMBO_BOX(packing_combobox));
    gtk_combo_box_get_active_iter(GTK_COMBO_BOX(packing_combobox), &iter);

    gchar *selected_packing;
    gtk_tree_model_get(model, &iter, 0, &selected_packing, -1);

    // Menampilkan nilai pilihan ComboBox
    g_print("Pilihan Packing: %s\n", selected_packing);

    // Mengambil nilai tambahan berdasarkan opsi packing
    TambahanPacking tambahan;

    if (g_strcmp0(selected_packing, "Packing Kayu 1") == 0) {
        tambahan.tambahan_panjang = 13;
        tambahan.tambahan_lebar = 5;
        tambahan.tambahan_tinggi = 5;
    } else if (g_strcmp0(selected_packing, "Packing Kayu 2") == 0) {
        tambahan.tambahan_panjang = 17;
        tambahan.tambahan_lebar = 9;
        tambahan.tambahan_tinggi = 9;
    } else if (g_strcmp0(selected_packing, "Packing Kayu 3") == 0) {
        tambahan.tambahan_panjang = 19;
        tambahan.tambahan_lebar = 12;
        tambahan.tambahan_tinggi = 12;
    } else if (g_strcmp0(selected_packing, "Packing Custom") == 0) {
        const char *custom_panjang_str = gtk_entry_get_text(GTK_ENTRY(entry_custom_panjang));
        const char *custom_lebar_str = gtk_entry_get_text(GTK_ENTRY(entry_custom_lebar));
        const char *custom_tinggi_str = gtk_entry_get_text(GTK_ENTRY(entry_custom_tinggi));

        tambahan.tambahan_panjang = atof(custom_panjang_str);
        tambahan.tambahan_lebar = atof(custom_lebar_str);
        tambahan.tambahan_tinggi = atof(custom_tinggi_str);
    } else {
        g_print("Opsi packing tidak valid!\n");
        // Anda dapat menangani kesalahan atau memberikan nilai default di sini
        return;
    }

    // Menghitung hasil sesuai rumus baru
    double hasil = (panjang + tambahan.tambahan_panjang) * 
                   (lebar + tambahan.tambahan_lebar) * 
                   (tinggi + tambahan.tambahan_tinggi) / harga;

    // Menampilkan hasil pada label
    char hasil_str[50];
    sprintf(hasil_str, "Hasil perhitungan: %.2f kg", hasil);

    gtk_label_set_text(GTK_LABEL(hasil_label), hasil_str);

    // Dealokasi memori dari selected_packing
    g_free(selected_packing);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "JNE Calculator");

    g_signal_connect(window, "destroy", G_CALLBACK(on_window_closed), NULL);

    GdkScreen *screen = gtk_window_get_screen(GTK_WINDOW(window));

    // Membuat grid container (GtkGrid)
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Menambahkan batas atas dan bawah pada grid
    gtk_widget_set_margin_top(grid, 10);
    gtk_widget_set_margin_bottom(grid, 10);
    gtk_widget_set_margin_start(grid, 10);
    gtk_widget_set_margin_end(grid, 10);

    // Menambahkan 4 label dan 4 textbox
    const char *label_texts[] = {"Panjang:", "Lebar:", "Tinggi:", "Harga:"};
    GtkWidget *textboxes[4];

    for (int i = 0; i < 4; ++i) {
        // Label
        GtkWidget *label = gtk_label_new(label_texts[i]);
        gtk_grid_attach(GTK_GRID(grid), label, 0, i, 1, 1);

        // Textbox
        GtkWidget *textbox = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(grid), textbox, 1, i, 1, 1);

        textboxes[i] = textbox;  // Menyimpan referensi ke setiap textbox
    }

    // Menambahkan ComboBox pada baris ke-7 dan kolom ke-0
    GtkWidget *packing_combobox = gtk_combo_box_text_new();
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(packing_combobox), NULL, "Packing Kayu 1");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(packing_combobox), NULL, "Packing Kayu 2");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(packing_combobox), NULL, "Packing Kayu 3");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(packing_combobox), NULL, "Packing Custom");  // Tambahkan opsi "Packing Custom"
    gtk_combo_box_set_active(GTK_COMBO_BOX(packing_combobox), 0);
    gtk_grid_attach(GTK_GRID(grid), packing_combobox, 1, 7, 1, 1);

    // Menambahkan label dan entry untuk nilai tambahan pada grid
    GtkWidget *label_custom = gtk_label_new("Packing Custom:");
    gtk_grid_attach(GTK_GRID(grid), label_custom, 0, 8, 1, 1);

    GtkWidget *entry_custom_panjang = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_custom_panjang, 1, 8, 1, 1);

    GtkWidget *entry_custom_lebar = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_custom_lebar, 2, 8, 1, 1);

    GtkWidget *entry_custom_tinggi = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_custom_tinggi, 3, 8, 1, 1);

    // Menambahkan tombol Hitung pada baris ke-9 dan kolom ke-0
    GtkWidget *hitung_button = gtk_button_new_with_label("Hitung");
    gtk_grid_attach(GTK_GRID(grid), hitung_button, 0, 9, 4, 1);

    // Menambahkan label hasil pada baris ke-10 dan kolom ke-0
    GtkWidget *hasil_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), hasil_label, 0, 10, 4, 1);

    // Mengatur window menjadi fullscreen
    gtk_window_fullscreen(GTK_WINDOW(window));

    // Menghubungkan fungsi callback pada tombol Hitung
    g_signal_connect(hitung_button, "clicked", G_CALLBACK(on_hitung_clicked), NULL);

    // Menyimpan referensi ke setiap textbox, ComboBox, dan hasil_label dalam objek tombol Hitung
    g_object_set_data(G_OBJECT(hitung_button), "panjang_entry", textboxes[0]);
    g_object_set_data(G_OBJECT(hitung_button), "lebar_entry", textboxes[1]);
    g_object_set_data(G_OBJECT(hitung_button), "tinggi_entry", textboxes[2]);
    g_object_set_data(G_OBJECT(hitung_button), "harga_entry", textboxes[3]);
    g_object_set_data(G_OBJECT(hitung_button), "tambahan_panjang_entry", textboxes[4]);
    g_object_set_data(G_OBJECT(hitung_button), "tambahan_lebar_entry", textboxes[5]);
    g_object_set_data(G_OBJECT(hitung_button), "tambahan_tinggi_entry", textboxes[6]);
    g_object_set_data(G_OBJECT(hitung_button), "packing_combobox", packing_combobox);
    g_object_set_data(G_OBJECT(hitung_button), "entry_custom_panjang", entry_custom_panjang);
    g_object_set_data(G_OBJECT(hitung_button), "entry_custom_lebar", entry_custom_lebar);
    g_object_set_data(G_OBJECT(hitung_button), "entry_custom_tinggi", entry_custom_tinggi);
    g_object_set_data(G_OBJECT(hitung_button), "hasil_label", hasil_label);

    // Menampilkan window
    gtk_widget_show_all(window);

    // Menjalankan loop utama GTK
    gtk_main();

    return 0;
}

