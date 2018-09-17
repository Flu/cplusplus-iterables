namespace cppit::regexEngine {
	class RegexObject {
		private:
			String regex, text;
			const String metaChars = "^$*+?";

		public:
		RegexObject(const String &_regex, const String &_text) {
			regex = _regex;
			text = _text;
		}

		int match();
		String replace();
		~RegexObject() {}
	};
} // namespace regex-engine

#include "regex.cpp"