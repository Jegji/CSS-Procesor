# CSS Processor

The objective of this project was to develop a simple CSS processor engine. It must to read CSS sections interleaved with command sections from standard input. The CSS sections should be parsed and placed into appropriate data structures, while the command sections should be parsed and executed, with the results printed to standard output (if any).

## CSS

Processing begins with the reading of CSS declarations. CSS is syntactically correct and consists of attribute blocks, optionally preceded by selectors. Lack of selectors is legal (indicating attributes applied to everything).

- Selectors are separated by commas. Legal CSS selectors are allowed, but it can be assumed they don't contain commas or curly braces.
- Attribute blocks are enclosed in curly braces.
- Attributes are separated by semicolons and consist of a name (property) and a value separated by a colon. A semicolon may or may not follow the last attribute in a block.
- Attribute values can include constructs legal for CSS, but for simplicity, it can be assumed that strings are not malicious, i.e., they don't contain escaped quotation marks, curly braces, or semicolons.
- If a specific attribute (name) appears more than once in a block, treat it as one occurrence, with the last value being significant.
- Both selectors and attribute names and values do not require semantic interpretation; they are treated as values after trimming leading and trailing whitespace. For instance, 'margin-left: 8px' and 'margin: 4px 7px 4px 7px' are treated as separate, unrelated attributes with names 'margin-left' and 'margin', and values '8px' and '4px 7px 4px 7px', respectively. Similarly, selectors are treated as values and do not require interpretation, i.e., 'h1' and 'h1.theme' are treated as separate, unrelated selectors.
- Simplification: CSS does not contain comments or @-type selectors, and blocks cannot be nested.
- For testing purposes, assume no selector, attribute, or block is split across multiple lines (multiple separators/attributes may appear in a single line).

## Commands

In the following commands, i and j are positive integers (fit into an int), while n is a legal attribute name.

- ???? – start of command section;
- **** - resume reading CSS;
- ? – print the number of CSS blocks;
- i,S,? – print the number of selectors for block number i (numbering starts from 1); if there's no such block, skip it;
- i,A,? - print the number of attributes for block number i; if there's no such block, skip it;
- i,S,j – print the j-th selector for block number i (block and attribute numbering starts from 1); if there's no block or selector, skip it;
- i,A,n – print the value of the attribute named n for block number i; if there's no such attribute, skip it;
- n,A,? – print the total (across all blocks) number of occurrences of the attribute named n. (Duplicates within a single block should be removed during parsing). It's possible to have 0 occurrences;
- z,S,? – print the total (across all blocks) number of occurrences of the selector z. It's possible to have 0 occurrences;
- z,E,n – print the value of the attribute named n for selector z. In case of multiple occurrences of selector z, take the last one. If there's no such occurrence, skip it;
- i,D,* - delete entire block number i (i.e., separators+attributes), if executed successfully, print 'deleted';
- i,D,n – delete the attribute named n from block number i; if, as a result of the operation, an empty block remains, it should also be deleted (along with any selectors). If executed successfully, print 'deleted'.

# Example
## Input
```
#breadcrumb 
{
	width: 80%;
	font-size: 9pt;
}

h1, body {
	min-width: 780px;
	margin: 0;
	padding: 0;
	font-family: "Trebuchet MS", "Lucida Grande", Arial;
	font-size: 85%;
	color: #666666;
}

h1, h2, h3, h4, h5, h6 {color: #0066CB;}
????
?
1,S,?
1,S,1
1,A,?
2,A,font-family
h1,S,?
color,A,?
h1,E,color
1,A,padding
1,D,*
?
2,D,color
?

****
h1, h2, h3, h4, h5, h6 {color: #0066FF;}
????
?
```
## Output
```
? == 3
1,S,? == 1
1,S,1 == #breadcrumb
1,A,? == 2
2,A,font-family == "Trebuchet MS", "Lucida Grande", Arial
h1,S,? == 2
color,A,? == 2
h1,E,color == #0066CB
1,D,* == deleted
? == 2
2,D, color == deleted
? == 1
? == 2
```


