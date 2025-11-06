using System;
using System.Net.Http;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

namespace NotesApp
{
    public class TranslationService
    {
        private readonly HttpClient _httpClient;

        public TranslationService()
        {
            _httpClient = new HttpClient();
        }

        public async Task<string> TranslateAsync(string text, string sourceLang, string targetLang)
        {
            if (string.IsNullOrWhiteSpace(text))
                return "";

            var payload = new
            {
                q = text,
                source = sourceLang,
                target = targetLang,
                format = "text"
            };

            string url = "https://libretranslate.de/translate";
            var content = new StringContent(JsonSerializer.Serialize(payload), Encoding.UTF8, "application/json");

            try
            {
                var response = await _httpClient.PostAsync(url, content);
                response.EnsureSuccessStatusCode();
                var result = await response.Content.ReadAsStringAsync();
                using var json = JsonDocument.Parse(result);
                if (json.RootElement.TryGetProperty("translatedText", out var node))
                    return node.GetString() ?? "";
                else
                    return "(翻訳失敗)";
            }
            catch (Exception ex)
            {
                return $"(翻訳エラー: {ex.Message})";
            }
        }
    }
}
