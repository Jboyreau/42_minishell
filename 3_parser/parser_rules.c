static void	rule_elem2(rules)
{
	static	rule_elem Parentheses[] = {};
	static	rule_elem Prefixe[] = {};
	static	rule_elem Prefixe1[] = {};
	static	rule_elem Suffixe[] = {};
	static	rule_elem Suffixe1[] = {};
	static	rule_elem Suffixe2[] = {};
	static	rule_elem Redirection[] = {};
	static	rule_elem Cmd2[] = {};
}

rule_elem	*init_rules()
{
	static	rule_elem prompt[] = {};
	static	rule_elem test[] = {};
	static	rule_elem test1[] = {};
	static	rule_elem test2[] = {};
	static	rule_elem nl[] = {};
	static	rule_elem nl1[] = {};
	static	rule_elem pipeline[] = {};
	static	rule_elem pipeline1[] = {};
	static	rule_elem Cmd[] = {};
	static	rule_elem Cmd1[] = {};

	return (rule_elem2(rules), prompt);
}
