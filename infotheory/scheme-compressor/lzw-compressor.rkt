#lang racket

(require "utils.rkt")

(define encoding-length 16)
(define max-size (expt 2 encoding-length))

(define (compress in out)
  (write-header out)
  (let f ((dico (init-dico)) (result '()) (w '()) (index 256))
    (let ((x (read-byte in)))
      (if (eof-object? x)
          (begin
            (write-result (binary-with-encoding-length
                                          (to-binary (hash-ref dico w)) encoding-length) out)
              (close-output-port out))
          (let ((temp (pair w x)))
            (if (hash-has-key? dico temp)
                (f dico result temp index)
                (begin
                  (hash-set! dico temp index)
                  (let ([result (write-result
                                 (append result
                                         (binary-with-encoding-length
                                          (to-binary (hash-ref dico w)) encoding-length)) out)]
                        [w (list x)])    
                    (if (>= index max-size)
                        (f (init-dico) result w 256)
                        (f dico result w (+ 1 index)))))))))))

(define (write-result l out)
  (if (> 8 (length l))
      l
      (let ((n (to-integer (take l 8))))
        (write-bytes (bytes n) out)
        (write-result (drop l 8) out))))


(define (init-dico)
  (let ([dico (make-hash)])
    (for ([i (in-range 256)])
      (hash-set! dico (list i) i))
    dico))

(define (write-header out)
  (write-bytes (bytes encoding-length) out))

(compress (open-input-file "/home/noe/Téléchargements/test.txt") (open-output-file "/home/noe/Téléchargements/out.bin" #:mode 'binary #:exists 'replace))