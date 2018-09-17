namespace cppit::regexEngine {
	
	int RegexObject::match() {
		int result = 0;
		if (regex[0] == '^')
			result += matchToken('^');
	}
} // namespace regex-engine