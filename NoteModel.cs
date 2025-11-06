namespace NotesApp
{
    public class NoteModel
    {
        public string Title { get; set; }
        public string Body { get; set; }
        public System.DateTime Date { get; set; }

        public override string ToString() => Title;
    }
}
