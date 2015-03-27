;; tested on guile 2.0.11, run as:
;; guile -e run-benchmark b4283.scm names.txt

(use-modules
 (ice-9 rdelim)
 (ice-9 format)
 (srfi srfi-1))

(define (count-names-first-letter L)
  (let ((a (map (lambda (x) (char-upcase (string-ref x 0))) L))
        (b (map integer->char (iota 26 65))))
    (map (lambda (x) (cons x (count (lambda (y) (char=? x y)) a))) b)))

(define (run-benchmark argv)
  (with-input-from-file (cadr argv)    
    (lambda ()
      (let F ((a '()) (b (read-line)))
        (if (eof-object? b)
            (let Q ((r (count-names-first-letter a)))
              (if (null? r)
                  'end-program
                  (let ((p (car r)))
                    (format #t "~c ~a\n" (car p) (cdr p))
                    (Q (cdr r)))))
            (F (cons b a) (read-line)))))))
                                      

