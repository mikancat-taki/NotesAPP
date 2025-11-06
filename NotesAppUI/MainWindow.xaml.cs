private void Search_Click(object sender, RoutedEventArgs e)
{
    string keyword = SearchBox.Text;
    string category = (CategoryBox.SelectedItem as ComboBoxItem)?.Content.ToString();
    var notes = DatabaseBridge.GetNotes(keyword, category);
    NotesList.ItemsSource = notes;
}

private void NotesList_SelectionChanged(object sender, SelectionChangedEventArgs e)
{
    var note = NotesList.SelectedItem as NoteModel;
    if (note != null)
    {
        TitleBox.Text = note.Title;
        NoteBox.Text = note.Body;
    }
}
