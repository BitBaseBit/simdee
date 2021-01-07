#pragma once


JVec_inline void simd4x4f_transpose_inplace(simd4x4f *s) {
    _MM_TRANSPOSE4_PS(s->x, s->y, s->z, s->w);
}

JVec_inline void simd4x4f_transpose(const simd4x4f *s, simd4x4f *out) {
    *out=*s;
    simd4x4f_transpose_inplace(out);
}



