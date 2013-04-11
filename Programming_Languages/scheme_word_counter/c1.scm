     ;scans search-list for existance of of char
     
     (define (exists? char . search-list)
       (let loop((list search-list))
         (if (null? list)
             #f
           (or (char=? char (car list)) (loop (cdr list))))
          )
       )
       
       (define (str-exists? char search-list)
         (define input (car search-list))
         
         (let loop((list input))
           (if (null? list)
               #f
                (if(string? (string (car list)) )
                  (begin
                    ;(display (string (car list))) (newline)
                    (or (string=? (string char) (string (car list)) ) (loop (cdr list) ) )
                  )
                  (begin
                    ;(display "not a string so looping wih empty list")
                    ;(display (string (car list)) ) (newline)
                    (loop '())
                  )
                )
                
             
             )
            )
       )
       
     ;take file input and counts characters, line, and words
     ;also creates and returns a list of words scanned from file
     
     (define (scan-file file)
       (with-input-from-file file
         (lambda ()
           (let loop((word '()) (word_list '()) (charcount 0) (wordcount 0) (linecount 0))
             (let ((char (read-char)))
     	  (cond
     	   ((eof-object? char)
                (if (pair? word)
                    (list  (cons ( string->symbol (list->string (reverse word) )) word_list) charcount wordcount linecount)
                    (list word_list charcount wordcount linecount)
                )
                 
            )
            
     	   ((exists? char #\newline)
                 (loop '() 
                        (if (pair? word)
                           (cons ( string->symbol (list->string (reverse word) )) word_list)
                           word_list
                        )
                        (+ charcount 1)
                        (if (null? word)
                            wordcount
                            (+ wordcount 1)
                        )
                        (+ linecount 1)
                  )
            )
            
            ((exists? char #\tab #\space)
                (loop '() 
                        (if (pair? word)
                           (cons ( string->symbol (list->string (reverse word) )) word_list)
                           word_list
                        )
                        (+ charcount 1)
                        (if (null? word)
                            wordcount
                            (+ wordcount 1)
                        )
                        (+ linecount 0)
                 )
            )
            
     	   (else
     	    (loop 
                (cons char word) 
                word_list 
                (+ charcount 1)
                (+ wordcount 0)
                (+ linecount 0))
           )))))))
     
     (define (print-map input-map) 
        (let loop( (map input-map) ) 
            (if (null? map)
                '()
                (begin
                    (display (string (car (car map)) )) (display " ") (display (cdr (car map))) (newline)
                    (loop(  cdr map  ))
                )
            )
        )
     
     )
     
     (define (fill-map input-map input-list) 
        (define map input-map)
        (let loop( (list input-list)  ) 
          (if (null? list)
               map
              (begin
                  (hash-table/put! map (car list) 0)
                  (loop(  cdr list  ))
              )
            )
        )
     
     )
     
     ;add 2nd arg for word file
     
     (define (wc file dictionary)
        (define scan_results (scan-file file))
        (define dict_results (scan-file dictionary))
        (define word_table (make-eq-hash-table))
         
        (fill-map word_table (car dict_results))
        ;define another result for word file scan
       (let ( 
                
                ( charcount ( cadr scan_results ) ) 
                ( wordcount ( caddr scan_results ) ) 
                ( linecount ( cadddr scan_results ) )
            )
         (let loop( ( word_list ( car scan_results ) ) )
           (if (null? word_list)
                (begin
                    (display linecount) (display " ")
                    (display wordcount) (display " ")
                    (display charcount) (display " ") (newline) (newline)
                    (display "Word usage:") (newline)
                    ( print-map (sort (hash-table->alist word_table) (lambda (x y) (> (cdr x) (cdr y)))) )
                    '()
                )

               (begin
                
                (if (str-exists? (car word_list) dict_results)
                  (begin
                    ;(display "Putting ") (display (car word_list)) (display " into table")(newline)
                    (hash-table/put! word_table (car word_list) (1+ (hash-table/get word_table (car word_list) 0)) )
                  )
                  '()
                )
             
              
              (loop (cdr word_list))))))
        )
